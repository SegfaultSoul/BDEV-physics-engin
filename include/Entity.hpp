#pragma once

#include "EntityVisual.hpp"
#include "PhysicsBody.hpp"
#include <string>

class Entity {
  protected:
    std::string name;
    int id;

  public:
    PhysicsBody body;
    EntityVisual visual;
    

    void init(int id, std::string name, Vector2D<double> position, Vector2D<double> size, double mass, ShapeType shape, double restitution);
    
    void set_id(int id);
    int get_id() const;

    void set_name(std::string name);
    std::string get_string() const;
};
