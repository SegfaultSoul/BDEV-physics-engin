#include "Entity.hpp"
#include "EntityVisual.hpp"

void Entity::init(
  int id, 
  std::string name,
  Vector2D<double> position, 
  Vector2D<double> size, 
  double mass, 
  ShapeType shape, 
  double restitution){
  this->set_id(id);
  this->set_name(name);
  this->body.set_position(position);
  this->body.set_mass(mass);
  this->body.set_size(size);
  this->body.set_restitution(restitution);
  this->visual.set_size(size);
  this->set_shape(shape);
}

void Entity::init(
  int id, 
  std::string name,
  Vector2D<double> position, 
  double radius, 
  double mass, 
  ShapeType shape, 
  double restitution){
  this->set_id(id);
  this->set_name(name);
  this->body.set_position(position);
  this->body.set_mass(mass);
  this->body.set_restitution(restitution);
  this->body.set_radius(radius);
  this->visual.set_radius(radius);
  this->set_shape(shape);
}

// setters
void Entity::set_id(int id) {
  this->id = id;
}

void Entity::set_name(std::string name) {
  this->name = name;
}

// getters
int Entity::get_id() const {
  return this->id;
}

std::string Entity::get_string() const {
  return this->name;
}

ShapeType Entity::get_shape() const {
  return this->shape;
}

void Entity::set_shape(ShapeType shape){
  this->shape = shape;
}

PhysicsBody* Entity::get_body() {
  return &this->body;
}

EntityVisual* Entity::get_visual() {
  return &this->visual;
}
