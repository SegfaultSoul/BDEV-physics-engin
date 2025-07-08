#include "PhysicsEngin.hpp"
#include "Entity.hpp"

void PhysicsEngin::add_entity(Entity* entity){
  this->entity_list.push_back(entity);
}

void PhysicsEngin::update(double dt){
  for (Entity* entity : entity_list) {
    if (entity->body.get_is_static()) continue;

    this->apply_force(entity, dt);
  }
}

void PhysicsEngin::apply_force(Entity* entity, double dt) {
  
}

