#include "Entity.hpp"
#include "Scene.hpp"
#include <iostream>
#include <SDL2/SDL.h>

int main(){
  
  Entity e;
  e.init(Vector2D<double>(150, 150), Vector2D<double>(150, 50), ShapeType::Rectangle);

  Scene s;
  s.init(660, 440, "test");
  
  s.add_entity(e);

  s.run();

  s.suspend();

  std::cout << "Process Terminated..." << "\n";
  return 0;
}
