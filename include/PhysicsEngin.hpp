#pragma once

#include "Entity.hpp"
#include <vector>
class PhysicsEngin{
  protected:
    std::vector<Entity*> entity_list = {};

    void apply_force(Entity* entity, double dt); 

  public:
    void add_entity(Entity* entity);

    void update(double dt);
};
