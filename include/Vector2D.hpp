#pragma once

#include <cmath>
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

    Vector2D<T> operator*(const double scaler){
      return Vector2D<T>(x * scaler, y * scaler);
    }

    Vector2D<T> operator/(const double scaler){
      return Vector2D<T>(x / scaler, y / scaler);
    }

    Vector2D<T>& operator+=(const Vector2D<T>& rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }

    Vector2D<T>& operator-=(const Vector2D<T>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      return *this;
    }

    T dot(const Vector2D<T>& rhs) {
      return (this->x * rhs.x) + (this->y * rhs.y);
    }

    Vector2D<T> perpendicular() {
      return Vector2D<T>(-this->y, this->x);
    }

    T magnitude() {
      return std::sqrt(x * x + y * y);
    }
};
