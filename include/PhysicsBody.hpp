#pragma once

#include "Vector2D.hpp"

class PhysicsBody {
  protected:
    Vector2D<double> position = {0, 0};
    Vector2D<double> size = {0, 0};
    Vector2D<double> velocity;
    Vector2D<double> acceleration;
    Vector2D<double> force;

    double mass = 1.0f;
    double inv_mass = 1.0f;

    bool is_static = false;

    // void apply_force(const Vector2D& force);
    // void update(float dt);
  
  public:
    void set_position(const Vector2D<double>& position);
    Vector2D<double> get_position() const;

    void set_size(const Vector2D<double>& size);
    Vector2D<double> get_size() const;

    void set_velocity(const Vector2D<double>& velocity);
    Vector2D<double> get_velocity() const;

    void set_acceleration(const Vector2D<double>& acceleration);
    Vector2D<double> get_acceleration() const;

    void set_force(const Vector2D<double>& force);
    Vector2D<double> get_force() const;

    void set_mass(double mass);
    double get_mass() const;
    double get_inv_mass() const;

    void set_is_static(bool is_static);
    bool get_is_static() const;

};
