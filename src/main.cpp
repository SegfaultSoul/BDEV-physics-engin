#include "Entity.hpp"
#include "Scene.hpp"
#include <iostream>
#include <SDL2/SDL.h>

int main(){
  
  Entity e;
  e.init(
      1, 
      "box 1", 
      Vector2D<double>(0, 0), 
      25,
      1.0f,
      ShapeType::Circle,
      0.8);

  e.get_body()->set_use_gravity(true);
  e.get_body()->set_impulse(Vector2D<double>(1000.0f, 1000.0f)); //(6500.0f, -5000.0f)
  
  Scene s;
  s.init(600, 600, "test", true);
  s.set_simulation_boundry_criteria(Vector2D<int>(550, 550), 25); 
  s.add_entity(e);

  s.set_gravity(Vector2D<double>(0.0f, 980.0f));
  s.set_time_scale(1.0f);

  s.run();

  s.suspend();

  std::cout << "Process Terminated..." << "\n";
  
  return 0;
}
