#include "EntityVisual.hpp"

void EntityVisual::set_position(Vector2D position){
  this->position = position;
}

void EntityVisual::set_size(Vector2D size){
  this->size = size;
}

void EntityVisual::set_scale(Vector2D scale){
  this->scale = scale;
}

void EntityVisual::set_visibility(bool is_visible){
  this->is_visible = is_visible;
}

void EntityVisual::set_shape(ShapeType shape){
  this->shape = shape;
}

void EntityVisual::set_radius(double radius){
  this->radius = radius;
}


