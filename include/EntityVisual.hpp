#pragma once

#include "Vector2D.hpp"

enum class ShapeType {
  None,
  Rectangel,
  Circle
};

class EntityVisual {
  public:
    Vector2D position;
    Vector2D scale = {1.0f, 1.0f};
    Vector2D size;

    bool is_visible = true;

    ShapeType shape;
    float radius;
};
