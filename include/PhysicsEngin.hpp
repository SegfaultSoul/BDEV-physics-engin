#pragma once

#include "Entity.hpp"
#include "PhysicsBody.hpp"
#include "Vector2D.hpp"
#include <vector>
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
