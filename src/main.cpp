#include "Entity.hpp"
#include "Scene.hpp"
#include <iostream>
#include <SDL2/SDL.h>

int main(){
  
  Entity e;
  e.init(
      1, 
      "box 1", 
      Vector2D<double>(150, 150), 
      Vector2D<double>(50, 50), 
      10.0f,
      ShapeType::Rectangle);

  e.body.set_use_gravity(true);
  e.body.set_impulse(Vector2D<double>(6500.0f, -5000.0f)); //(6500.0f, -5000.0f)
  
  Scene s;
  s.init(1200, 600, "test");
  
  s.add_entity(e);

  s.set_gravity(Vector2D<double>(0.0f, 980.0f));
  s.set_time_scale(1.0f);
  
  s.run();

  s.suspend();

  std::cout << "Process Terminated..." << "\n";
  return 0;
}
