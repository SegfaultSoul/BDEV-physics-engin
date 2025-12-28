#pragma once

#include "Vector2D.hpp"
#include <vector>

class PhysicsBody {
  protected:
    Vector2D<double> position = {0, 0};
    Vector2D<double> size = {0, 0};
    double radius = 0.0;
    Vector2D<double> velocity = {0, 0};
    Vector2D<double> acceleration = {0, 0};
    

    Vector2D<double> force = {0, 0};
    Vector2D<double> impulse = {0, 0};

    double mass = 1.0f;
    double inv_mass = 1.0f;

    double restitution = 1;

    bool is_static = false;
    bool use_gravity = true;

    // void apply_force(const Vector2D& force);
    // void update(float dt);
  
  public:
    void set_position(const Vector2D<double>& position);
    Vector2D<double> get_position() const;

    void set_size(const Vector2D<double>& size);
    Vector2D<double> get_size() const;

    void set_radius(double radius);
    double get_radius() const;
    
    void set_velocity(const Vector2D<double>& velocity);
    Vector2D<double> get_velocity() const;

    void set_acceleration(const Vector2D<double>& acceleration);
    Vector2D<double> get_acceleration() const;

    void set_force(const Vector2D<double>& force);
    Vector2D<double> get_force() const;

    void set_impulse(const Vector2D<double>& impulse);
    Vector2D<double> get_impulse() const;

    void set_mass(double mass);
    double get_mass() const;
    double get_inv_mass() const;

    void set_is_static(bool is_static);
    bool get_is_static() const;
    
    void set_use_gravity(bool use_gravity);
    bool get_use_gravity() const;

    void set_restitution(double restitution);
    double get_restitution() const;

    std::vector<Vector2D<double>> get_points() const;
    std::vector<Vector2D<double>> get_edges() const;
};
