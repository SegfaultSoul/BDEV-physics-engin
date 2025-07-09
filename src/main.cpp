#include "Entity.hpp"
#include "Scene.hpp"
#include <iostream>
#include <SDL2/SDL.h>

int main(){
  
  Entity e;
  e.init(Vector2D<double>(150, 150), Vector2D<double>(150, 50), 10.0f,ShapeType::Rectangle);
  e.body.set_use_gravity(false);
  Scene s;
  s.init(1200, 600, "test");
  
  s.add_entity(e);

  s.set_gravity(Vector2D<double>(0.0f, 980.0f));

  s.run();

  s.suspend();

  std::cout << "Process Terminated..." << "\n";
  return 0;
}
