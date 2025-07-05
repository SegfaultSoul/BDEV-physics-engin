#pragma once

class Vector2 {
public:
    float x, y;

    // Constructor
    Vector2(float x = 0.0f, float y = 0.0f);

    // Operator Overloads
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(const Vector2& rhs) const;
    Vector2 operator/(const Vector2& rhs) const;
    Vector2 operator+=(const Vector2& rhs);
};

class PhysicsBody {
  protected:
    
};
