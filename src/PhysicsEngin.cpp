#include "PhysicsEngin.hpp"
#include "Entity.hpp"
#include "PhysicsBody.hpp"
#include "Vector2D.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <optional>
#include <vector>

void PhysicsEngin::add_entity(Entity* entity){
  this->entity_list.push_back(entity);
}

void PhysicsEngin::update(double dt){
  std::vector<CollisionPair> colliding_pairs = broad_phase(entity_list);

  std::vector<ResolutionPair> resolution_pairs = narrow_phase(colliding_pairs);

  relove_narrow_phase(resolution_pairs);
  
  for (Entity* entity : entity_list) {
    PhysicsBody* entity_body = entity->get_body();
    if (entity_body->get_is_static()) continue;

    this->clear_force(entity_body);
 
    this->apply_gravity(entity_body);
    this->apply_force(entity_body);
    this->apply_impulse(entity_body);

    this->integrate_forces(entity_body, dt);
  }

  for (Entity* entity: entity_list) {
    PhysicsBody* entity_body = entity->get_body();
    if (entity_body->get_is_static()) continue;
  
    this->integrate_velocity(entity_body, dt);
    this->resolve_boundry_collisions(entity);
  }
}

void PhysicsEngin::apply_force(PhysicsBody* entity_body) {
  //TODO
}

void PhysicsEngin::apply_gravity(PhysicsBody* entity_body) {
  if (!entity_body->get_use_gravity()) return;
  entity_body->set_force(entity_body->get_force() + this->get_gravity() * entity_body->get_mass());
}

void PhysicsEngin::apply_impulse(PhysicsBody* entity_body) {
  Vector2D<double> impulse = entity_body->get_impulse();
  if (impulse.x == 0 && impulse.y == 0) return;

  Vector2D<double> acc_from_impulse = impulse * entity_body->get_inv_mass();
  entity_body->set_velocity(entity_body->get_velocity() + acc_from_impulse);
  entity_body->set_impulse(Vector2D<double>(0, 0));
}

void PhysicsEngin::integrate_forces(PhysicsBody* entity_body, double dt) {
  Vector2D<double> acceleration =
    entity_body->get_force() * entity_body->get_inv_mass();

  entity_body->set_velocity(
    entity_body->get_velocity() + acceleration * dt
  );
}

void PhysicsEngin::integrate_velocity(PhysicsBody* entity_body, double dt) {
  entity_body->set_position(
    entity_body->get_position() + entity_body->get_velocity() * dt
  );
}

void PhysicsEngin::clear_force(PhysicsBody* entity_body) {
  entity_body->set_force(Vector2D<double>(0, 0));
}

void PhysicsEngin::set_gravity(const Vector2D<double>& gravity) {
  this->gravity = gravity;
}

Vector2D<double> PhysicsEngin::get_gravity() const {
  return this->gravity;
}

void PhysicsEngin::set_boundry(const Vector2D<int>& dim){
  this->height = dim.y;
  this->width = dim.x;
}

Vector2D<int> PhysicsEngin::get_boundry() const {
  return Vector2D<int>(this->height, this->width);
}

int PhysicsEngin::get_height() const {
  return this->height;
}

int PhysicsEngin::get_width() const {
  return this->width;
}

Vector2D<int> PhysicsEngin::get_bounds_offset() const {
  return this->bounds_offset;
}

void PhysicsEngin::set_bounds_offset(const Vector2D<int>& offset) {
  this->bounds_offset = offset;
}

void PhysicsEngin::resolve_boundry_collisions(Entity* entity) const {
    Vector2D<double> position  = entity->get_body()->get_position();
    Vector2D<double> velocity  = entity->get_body()->get_velocity();
    Vector2D<double> half_size;
    if (entity->get_shape() == ShapeType::Rectangle) {
      half_size = entity->get_body()->get_size() * 0.5;
    }

    if (entity->get_shape() == ShapeType::Circle) {
      double radius = entity->get_body()->get_radius();
      half_size = {radius, radius};
    }
    
    double restitution = entity->get_body()->get_restitution();

    double worldLeft   = bounds_offset.x;
    double worldRight  = bounds_offset.x + width;
    double worldTop    = bounds_offset.y + height;
    double worldBottom = bounds_offset.y;

    // --- Horizontal ---
    if (position.x - half_size.x < worldLeft) {
        position.x = worldLeft + half_size.x;
        if (velocity.x < 0.0)
            velocity.x = -velocity.x * restitution;
    }
    else if (position.x + half_size.x > worldRight) {
        position.x = worldRight - half_size.x;
        if (velocity.x > 0.0)
            velocity.x = -velocity.x * restitution;
    }

    // --- Vertical ---
    if (position.y - half_size.y < worldBottom) {
        position.y = worldBottom + half_size.y;
        if (velocity.y < 0.0)
            velocity.y = -velocity.y * restitution;
    }
    else if (position.y + half_size.y > worldTop) {
        position.y = worldTop - half_size.y;
        if (velocity.y > 0.0)
            velocity.y = -velocity.y * restitution;
    }

    entity->get_body()->set_position(position);
    entity->get_body()->set_velocity(velocity);
}

std::vector<ResolutionPair> PhysicsEngin::narrow_phase(std::vector<CollisionPair>& colliding_pairs) {
  std::vector<ResolutionPair> resolution_pairs;

  for (CollisionPair& cp: colliding_pairs) {
    if (std::optional<ResolutionPair> rp = sat_collision_check(cp)) {
      resolution_pairs.emplace_back(std::move(*rp));
    }
  }

  return resolution_pairs;
}

//TODO: Add the actual entity collision check in the update
std::optional<ResolutionPair> PhysicsEngin::sat_collision_check(CollisionPair& pair) {
  PhysicsBody *entity_1 = pair.entity_1->get_body(), *entity_2 = pair.entity_2->get_body();

  double min_overlap = INFINITY;
  Vector2D<double> collision_normal {};

  std::vector<Vector2D<double>> points_1 = entity_1->get_points();
  std::vector<Vector2D<double>> points_2 = entity_2->get_points();
  
  //get the edges of both entities 
  std::vector<Vector2D<double>> unit_axis = entity_1->get_edges();
  std::vector<Vector2D<double>> edges_ = entity_2->get_edges();

  //combine the edges 
  unit_axis.reserve(unit_axis.size() + edges_.size());
  unit_axis.insert(unit_axis.end(), edges_.begin(), edges_.end());

  //get the unit axis via perpendicular of the edge divided by its magnitude
  for(Vector2D<double>& vec: unit_axis) {
    vec = vec.perpendicular();
    if (vec.magnitude() == 0.0) continue;
    vec = vec / vec.magnitude();
  }

  for(Vector2D<double>& axis: unit_axis){
    bool is_colliding = true;
    
    this->_sat_projection_check(
      points_1,
      points_2,
      axis,
      is_colliding,
      min_overlap,
      collision_normal);
    
    if(!is_colliding) return std::nullopt;
  }
  
  Vector2D<double> center_dir = entity_2->get_position() - entity_1->get_position();
  if (center_dir.dot(collision_normal) < 0) {
    collision_normal = -collision_normal;
  }
  
  return ResolutionPair(pair, collision_normal, min_overlap);
}

void PhysicsEngin::_sat_projection_check(
  std::vector<Vector2D<double>>& points_1,
  std::vector<Vector2D<double>>& points_2,
  Vector2D<double>& axis,
  bool& is_colliding,
  double& min_overlap,
  Vector2D<double>& collision_normal) const {
  double max_a = -INFINITY, min_a = INFINITY, max_b = -INFINITY, min_b = INFINITY;
  
  for (Vector2D<double>& point : points_1) {
    double proj = point.dot(axis);
    if (min_a > proj) min_a = proj;
    if (max_a < proj) max_a = proj;
  }

  for (Vector2D<double>& point : points_2) {
    double proj = point.dot(axis);
    if (min_b > proj) min_b = proj;
    if (max_b < proj) max_b = proj;
  }

  if(max_a < min_b || max_b < min_a) {
    is_colliding = false;
    return;
  }
  
  double overlap = std::min(max_a, max_b) - std::max(min_a, min_b);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    collision_normal = axis;  
  }
}

AABB<double> PhysicsEngin::_compute_AABB(Entity* entity) const {
  AABB<double> output;
  output.entity = entity;
  std::vector<Vector2D<double>> points = entity->get_body()->get_points();
  output.min = output.max = points[0];

  for(const Vector2D<double>& point: points) {
    output.min.x = std::min(output.min.x, point.x);
    output.min.y = std::min(output.min.y, point.y);
    output.max.x = std::max(output.max.x, point.x);
    output.max.y = std::max(output.max.y, point.y);
  }
  return output;
}

bool PhysicsEngin::_check_AABB(
  const AABB<double>& entity_1, 
  const AABB<double>& entity_2) const {
  return !( entity_1.max.x < entity_2.min.x ||
            entity_1.min.x > entity_2.max.x ||
            entity_1.max.y < entity_2.min.y ||
            entity_1.min.y > entity_2.max.y );
}


std::vector<CollisionPair> PhysicsEngin::broad_phase(std::vector<Entity*> entities) {
  std::vector<CollisionPair> pairs;
  
  std::vector<AABB<double>> intervals;
  intervals.reserve(entities.size());

  for (Entity* e : entities) {
    intervals.push_back(_compute_AABB(e));
  }

  std::sort(intervals.begin(), intervals.end(),
    [](AABB<double>& entity_a, AABB<double>& entity_b){
      return entity_a.min.x < entity_b.min.x;
    });  
  
  for (std::size_t i = 0; i < intervals.size(); ++i) {
    for (std::size_t j = i + 1; j < intervals.size(); ++j) {
      
      if (intervals[j].min.x > intervals[i].max.x) break;

      if( intervals[j].min.y > intervals[i].max.y ||
          intervals[j].max.y < intervals[i].min.y) continue;

      pairs.emplace_back(intervals[i].entity, intervals[j].entity);
    }
  }
  
  return pairs;
}

void PhysicsEngin::relove_narrow_phase(std::vector<ResolutionPair>& rps) {
  for(ResolutionPair& rp: rps) {
    PhysicsBody* entity_1 = rp.pair.entity_1->get_body();
    PhysicsBody* entity_2 = rp.pair.entity_2->get_body();

    double inv_mass_1 = entity_1->get_inv_mass();
    double inv_mass_2 = entity_2->get_inv_mass();
    double total_inv_mass = inv_mass_1 + inv_mass_2;

    if (total_inv_mass == 0.0) continue;
    
    constexpr double k_slop = 1.0f;
    constexpr double percent = 0.8f;

    double corrected_overlap = std::max(rp.overlap - k_slop, 0.0);

    Vector2D<double> correction = rp.normal * (corrected_overlap / total_inv_mass) * percent;

    entity_1->set_position(entity_1->get_position() - correction * inv_mass_1);
    entity_2->set_position(entity_2->get_position() + correction * inv_mass_2);
  
    Vector2D<double> rel_vel = entity_2->get_velocity() - entity_1->get_velocity();
    double normal_rel_vel = rel_vel.dot(rp.normal);
    if (normal_rel_vel > 0.0) continue;

    double e = std::min(entity_1->get_restitution(), entity_2->get_restitution());
    double j = -(1 + e) * normal_rel_vel;
    j /= total_inv_mass;

    Vector2D<double> impulse = rp.normal * j;
    entity_1->set_impulse(entity_1->get_impulse() - impulse);
    entity_2->set_impulse(entity_2->get_impulse() + impulse);
  }
}
