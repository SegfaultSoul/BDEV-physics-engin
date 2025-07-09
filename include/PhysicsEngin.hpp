#pragma once

#include "Entity.hpp"
#include "Vector2D.hpp"
#include <vector>
class PhysicsEngin{
  protected:
    std::vector<Entity*> entity_list = {};
    Vector2D<double> gravity = {0, 9.8f};

    void apply_force(Entity* entity, double dt); 
    void apply_gravity(Entity* entity, double dt);


  public:
    void add_entity(Entity* entity);

    void update(double dt);

    void set_gravity(const Vector2D<double>& gravity);
    Vector2D<double> get_gravity() const;
};
