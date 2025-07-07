#pragma once

#include "Vector2D.hpp"
#include <numbers>

enum class ShapeType {
  None,
  Rectangel,
  Circle
};

class EntityVisual {
  protected:
    Vector2D position;
    Vector2D scale = {1.0f, 1.0f};
    Vector2D size;

    bool is_visible = true;

    ShapeType shape = ShapeType::None;
    double radius = std::numbers::pi;

  public:
    void set_position(Vector2D position);
    void set_size(Vector2D size);
    void set_scale(Vector2D scale);

    void set_visibility(bool is_visible);

    void set_shape(ShapeType shape);
    void set_radius(double radius);

};
