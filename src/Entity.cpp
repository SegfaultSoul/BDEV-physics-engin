#include "Entity.hpp"
#include "EntityVisual.hpp"

void Entity::init(Vector2D<double> position, Vector2D<double> size, ShapeType shape){
  this->body.set_position(position);
  this->visual.set_size(size);
  this->visual.set_shape(shape);
}
