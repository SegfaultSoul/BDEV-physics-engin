#include "PhysicsEngin.hpp"
#include "Entity.hpp"
#include "PhysicsBody.hpp"
#include "Vector2D.hpp"
#include <iostream>

void PhysicsEngin::add_entity(Entity* entity){
  this->entity_list.push_back(entity);
}

void PhysicsEngin::update(double dt){
  for (Entity* entity : entity_list) {
    if (entity->body.get_is_static()) continue;

    this->apply_impulse(entity, dt);
    this->apply_gravity(entity, dt);
    this->integrate(entity, dt);
    // this->apply_force(entity, dt);
  }
}

void PhysicsEngin::apply_force(Entity* entity, double dt) {
  
}

void PhysicsEngin::apply_gravity(Entity* entity, double dt) {
  if (!entity->body.get_use_gravity()) return;
  
  PhysicsBody& body = entity->body;
  body.set_force(this->get_gravity() * body.get_mass());
  
  body.set_acceleration(body.get_acceleration() + body.get_force() * body.get_inv_mass());
}

void PhysicsEngin::apply_impulse(Entity* entity, double dt) {
  PhysicsBody& body = entity->body;
  Vector2D<double> impulse = body.get_impulse();
  if (impulse.x == 0 || impulse.y == 0) return;

  Vector2D<double> acc_from_impulse = impulse * body.get_inv_mass();
  body.set_velocity(body.get_velocity() + acc_from_impulse);
  body.set_impulse(Vector2D<double>(0, 0));
}

void PhysicsEngin::integrate(Entity* entity, double dt) {
  PhysicsBody& body = entity->body;

  body.set_velocity(body.get_velocity() + body.get_acceleration() * dt);
  body.set_position(body.get_position() + body.get_velocity() * dt);

  body.set_acceleration(Vector2D<double>(0, 0));
}

void PhysicsEngin::set_gravity(const Vector2D<double>& gravity) {
  this->gravity = gravity;
}

Vector2D<double> PhysicsEngin::get_gravity() const {
  return this->gravity;
}
