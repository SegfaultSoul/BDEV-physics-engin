#pragma once

#include "Vector2D.hpp"

class PhysicsBody {
  protected:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D force;

    double mass = 1.0f;

    bool is_static = false;

    // void apply_force(const Vector2D& force);
    // void update(float dt);
};
