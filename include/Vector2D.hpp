#pragma once

#include <type_traits>

template<typename T>
requires std::is_arithmetic_v<T>
class Vector2D {
  public:
    T x, y;

    // Constructor
    Vector2D(T x = 0, T y = 0): x(x), y(y) {}

    // Operator Overloads
    Vector2D<T> operator+(const Vector2D<T>& rhs) const {
      return Vector2D<T>(x + rhs.x, y + rhs.y);
    }

    Vector2D<T> operator-(const Vector2D<T>& rhs) const {
      return Vector2D<T>(x - rhs.x, y - rhs.y);
    }

    Vector2D<T> operator*(const Vector2D<T>& rhs) const {
      return Vector2D<T>(x * rhs.x, y * rhs.y);
    }
    
    Vector2D<T> operator/(const Vector2D<T>& rhs) const {
      return Vector2D<T>(x / rhs.x, y / rhs.y);
    }

    Vector2D<T> operator+=(const Vector2D<T>& rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }
};
