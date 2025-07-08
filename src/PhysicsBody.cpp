#include "PhysicsBody.hpp"
#include "Vector2D.hpp"

void PhysicsBody::set_position(Vector2D<double> position){
  this->position = position;
}

Vector2D<double> PhysicsBody::get_position() const {
  return this->position;
}
