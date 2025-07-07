#pragma once

class Vector2D {
public:
    float x, y;

    // Constructor
    Vector2D(float x = 0.0f, float y = 0.0f);

    // Operator Overloads
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator*(const Vector2D& rhs) const;
    Vector2D operator/(const Vector2D& rhs) const;
    Vector2D operator+=(const Vector2D& rhs);
};
