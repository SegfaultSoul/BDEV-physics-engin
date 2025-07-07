#include "Vector2D.hpp"

Vector2D::Vector2D (double x, double y): x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& rhs) const {
  return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const {
  return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const {
  return Vector2D(x * rhs.x, y * rhs.y);
}

Vector2D Vector2D::operator/(const Vector2D& rhs) const {
  return Vector2D(x / rhs.x, y / rhs.y);
}

Vector2D Vector2D::operator+=(const Vector2D& rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}
