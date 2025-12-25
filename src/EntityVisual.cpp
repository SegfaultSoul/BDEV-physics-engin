#include "EntityVisual.hpp"
#include "SDL_pixels.h"
#include "Vector2D.hpp"

// Setters
void EntityVisual::set_size(const Vector2D<double>& size){
  this->size = size;
}

void EntityVisual::set_scale(const Vector2D<double>& scale){
  this->scale = scale;
}

void EntityVisual::set_visibility(bool is_visible){
  this->is_visible = is_visible;
}

void EntityVisual::set_radius(double radius){
  this->radius = radius;
}

void EntityVisual::set_color(SDL_Color color) {
  this->color = color;
}


// getters
Vector2D<double> EntityVisual::get_size() const {
  return this->size;
}

Vector2D<double> EntityVisual::get_scale() const {
  return this->scale;
}

bool EntityVisual::get_visibility() const {
  return this->is_visible;
}

double EntityVisual::get_radius() const {
  return this->radius;
}

SDL_Color EntityVisual::get_color() const {
  return this->color;
}
