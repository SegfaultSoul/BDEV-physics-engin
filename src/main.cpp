#include "Entity.hpp"
#include "Scene.hpp"
#include <iostream>
#include <SDL2/SDL.h>

int main(){
  
  Entity e;
  e.body.set_position(Vector2D<double>(25, 25));
  e.visual.set_shape(ShapeType::Rectangle);
  e.visual.set_size(Vector2D<double>(50, 50));

  Scene s;
  s.init(660, 440, "test");
  
  s.add_entity(e);

  s.run();

  s.suspend();

  std::cout << "Process Terminated..." << "\n";
  return 0;
}
