#pragma once

#include "EntityVisual.hpp"
#include "PhysicsBody.hpp"

class Entity {
  public:
    PhysicsBody body;
    EntityVisual visual;
    
    void init(Vector2D<double> position, Vector2D<double> size, ShapeType);

};
