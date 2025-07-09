#include "PhysicsBody.hpp"
#include "Vector2D.hpp"


// setters
void PhysicsBody::set_position(const Vector2D<double>& position){
  this->position = position;
}

void PhysicsBody::set_size(const Vector2D<double>& size){
  this->size = size;
}

void PhysicsBody::set_velocity(const Vector2D<double>& velocity){
  this->velocity = velocity;
}

void PhysicsBody::set_acceleration(const Vector2D<double>& acceleration){
  this->acceleration = acceleration;
}

void PhysicsBody::set_force(const Vector2D<double>& force){
  this->force = force;
}

void PhysicsBody::set_mass(double mass){
  this->mass = mass;
  this->inv_mass = (mass == 0.0 || is_static) ? 0.0 : 1.0 / mass;
}

void PhysicsBody::set_is_static(bool is_static){
  this->is_static = is_static;
  this->inv_mass = is_static ? 0.0 : (mass == 0.0 ? 0.0 : 1.0 / mass);
}

void PhysicsBody::set_use_gravity(bool use_gravity) {
  this->use_gravity = use_gravity;
}

void PhysicsBody::set_impulse(const Vector2D<double>& impulse) {
  this->impulse = impulse;
}

// getters
Vector2D<double> PhysicsBody::get_position() const {
  return this->position;
}

Vector2D<double> PhysicsBody::get_size() const {
  return this->size;  
}

Vector2D<double> PhysicsBody::get_velocity() const {
  return this->velocity;
}

Vector2D<double> PhysicsBody::get_acceleration() const {
  return this->acceleration;
}

Vector2D<double> PhysicsBody::get_force() const {
  return this->force;
}

double PhysicsBody::get_mass() const {
  return this->mass;
}

double PhysicsBody::get_inv_mass() const {
  return this->inv_mass;
}

bool PhysicsBody::get_is_static() const {
  return this->is_static;
}

bool PhysicsBody::get_use_gravity() const {
  return this->use_gravity;
}

Vector2D<double> PhysicsBody::get_impulse() const {
  return this->impulse;
}
