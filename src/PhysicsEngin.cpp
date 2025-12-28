#include "PhysicsEngin.hpp"
#include "Entity.hpp"
#include "PhysicsBody.hpp"
#include "Vector2D.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

void PhysicsEngin::add_entity(Entity* entity){
  this->entity_list.push_back(entity);
}

void PhysicsEngin::update(double dt){
  for (Entity* entity : entity_list) {
    PhysicsBody* entity_body = entity->get_body();
    if (entity_body->get_is_static()) continue;

    this->clear_force(entity_body);
 
    this->apply_gravity(entity_body);
    this->apply_force(entity_body);
    this->apply_impulse(entity_body);

    this->integrate_forces(entity_body, dt);
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
    double worldTop    = bounds_offset.y;
    double worldBottom = bounds_offset.y + height;

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
    if (position.y - half_size.y < worldTop) {
        position.y = worldTop + half_size.y;
        if (velocity.y < 0.0)
            velocity.y = -velocity.y * restitution;
    }
    else if (position.y + half_size.y > worldBottom) {
        position.y = worldBottom - half_size.y;
        if (velocity.y > 0.0)
            velocity.y = -velocity.y * restitution;
    }

    entity->get_body()->set_position(position);
    entity->get_body()->set_velocity(velocity);
}

//TODO: Add the actual entity collision check in the update
bool PhysicsEngin::sat_collision_check(PhysicsBody* entity_1, PhysicsBody* entity_2) {
  bool is_colliding = true;

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
  edges_.clear();

  //get the unit axis via perpendicular of the edge divided by its magnitude
  for(Vector2D<double>& vec: unit_axis) {
    vec = vec.perpendicular();
    vec = vec / vec.magnitude();
  }

  for(Vector2D<double>& axis: unit_axis){
    if(!is_colliding) break;
    this->_sat_porjection_check(
      points_1,
      points_2,
      axis,
      is_colliding,
      min_overlap,
      collision_normal);
  }
  
  
  return is_colliding;
}

void PhysicsEngin::_sat_porjection_check(
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

  if(max_a < min_b || max_b < min_a) is_colliding = false;
  
  double overlap = std::min(max_a, max_b) - std::max(min_a, min_b);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    collision_normal = axis;  
  }
}

