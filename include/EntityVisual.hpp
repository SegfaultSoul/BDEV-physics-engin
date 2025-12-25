#pragma once

#include "SDL_pixels.h"
#include "Vector2D.hpp"
#include <numbers>

class EntityVisual {
  protected:
    Vector2D<double> scale = {1.0f, 1.0f};
    Vector2D<double> size = {1.0, 1.0};

    bool is_visible = true;

    double radius = std::numbers::pi;

    SDL_Color color = {255, 255, 255, 255};

  public:
    void set_size(const Vector2D<double>& size);
    Vector2D<double> get_size() const;

    void set_scale(const Vector2D<double>& scale);
    Vector2D<double> get_scale() const;

    void set_visibility(bool is_visible);
    bool get_visibility() const;

    void set_radius(double radius);
    double get_radius() const;

    void set_color(SDL_Color color);
    SDL_Color get_color() const;

};


