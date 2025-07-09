#include "Entity.hpp"
#include "EntityVisual.hpp"

void Entity::init(Vector2D<double> position, Vector2D<double> size, double mass, ShapeType shape){
  this->body.set_position(position);
  this->body.set_mass(mass);
  this->body.set_size(size);
  this->visual.set_size(size);
  this->visual.set_shape(shape);
}
