#pragma once

#include "Entity.hpp"
#include "PhysicsBody.hpp"
#include "Vector2D.hpp"
#include <cmath>
#include <optional>
#include <vector>

template<typename T>
struct AABB {
  Entity* entity;
  Vector2D<T> max;
  Vector2D<T> min;
};

struct CollisionPair {
  Entity *entity_1, *entity_2;

  CollisionPair(Entity* a_, Entity* b_): entity_1(a_), entity_2(b_) {}
};

struct ResolutionPair {
  CollisionPair& pair;
  Vector2D<double> normal;
  double overlap;

  ResolutionPair(
      CollisionPair& pair_, 
      Vector2D<double> normal_, 
      double overlap_ = INFINITY): 
    pair(pair_), 
    normal(normal_), 
    overlap(overlap_) {}
};

class PhysicsEngin{
  protected:
    std::vector<Entity*> entity_list = {};
    Vector2D<double> gravity = {0, 980.0f};

    Vector2D<int> bounds_offset = {0 ,0};
    int height = 0;
    int width = 0;

    void apply_force(PhysicsBody* entity_body); 
    void apply_gravity(PhysicsBody* entity_body);
    void apply_impulse(PhysicsBody* entity_body);
    void integrate_forces(PhysicsBody* entity_body, double dt);
    void integrate_velocity(PhysicsBody* entity_body, double dt);
    void clear_force(PhysicsBody* entity_body);

    void resolve_boundry_collisions(Entity* entity) const;

    std::optional<ResolutionPair> sat_collision_check(CollisionPair& pair);
    void _sat_projection_check(
      std::vector<Vector2D<double>>& points_1,
      std::vector<Vector2D<double>>& points_2,
      Vector2D<double>& axis,
      bool& is_colliding,
      double& min_overlap,
      Vector2D<double>& collision_normal) const;
  
    AABB<double> _compute_AABB(Entity* entity) const;
    bool _check_AABB(const AABB<double>& entity_1, const AABB<double>& entity_2) const;

    std::vector<CollisionPair> broad_phase(std::vector<Entity*> entities);

    std::vector<ResolutionPair> narrow_phase(std::vector<CollisionPair>& colliding_pairs);

  public:
    void add_entity(Entity* entity);

    void update(double dt);

    void set_gravity(const Vector2D<double>& gravity);
    Vector2D<double> get_gravity() const;

    void set_boundry (const Vector2D<int>& dim);
    Vector2D<int> get_boundry() const;
    int get_height() const;
    int get_width() const;

    Vector2D<int> get_bounds_offset() const;
    void set_bounds_offset(const Vector2D<int>& offset);
};
