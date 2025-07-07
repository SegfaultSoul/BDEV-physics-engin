#pragma once

class Vector2D {
public:
    double x, y;

    // Constructor
    Vector2D(double x = 0.0f, double y = 0.0f);

    // Operator Overloads
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator*(const Vector2D& rhs) const;
    Vector2D operator/(const Vector2D& rhs) const;
    Vector2D operator+=(const Vector2D& rhs);
};
