#include "PhysicsBody.hpp"

Vector2::Vector2 (float x, float y): x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& rhs) const {
  return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
  return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const Vector2& rhs) const {
  return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator/(const Vector2& rhs) const {
  return Vector2(x / rhs.x, y / rhs.y);
}

Vector2 Vector2::operator+=(const Vector2& rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}
