#pragma once

#include "EntityVisual.hpp"
#include "PhysicsBody.hpp"

class Entity {
  public:
    PhysicsBody body;
    EntityVisual visual;
};
