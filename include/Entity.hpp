#pragma once

#include "EntityVisual.hpp"
#include "PhysicsBody.hpp"
#include <string>

enum class ShapeType {
  None,
  Rectangle,
  Circle
};

class Entity {
  protected:
    PhysicsBody body;
    EntityVisual visual;
 
    std::string name;
    int id;

    ShapeType shape = ShapeType::None;
  
  public:
    

    void init(
      int id, 
      std::string name, 
      Vector2D<double> position, 
      Vector2D<double> size, 
      double mass, 
      ShapeType shape, 
      double restitution);
    
    void init(
      int id, 
      std::string name, 
      Vector2D<double> position, 
      double radius, 
      double mass, 
      ShapeType shape, 
      double restitution);
    
    void set_id(int id);
    int get_id() const;

    void set_name(std::string name);
    std::string get_string() const;

    void set_shape(ShapeType shape);
    ShapeType get_shape() const;

    PhysicsBody* get_body();
    EntityVisual* get_visual();
};
