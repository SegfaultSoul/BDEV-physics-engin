#pragma once

#include "EntityVisual.hpp"
#include "PhysicsBody.hpp"

class Entity {
  public:
    PhysicsBody physics;
    EntityVisual visual;
};
