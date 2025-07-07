#include "Scene.hpp"
#include <iostream>
#include <SDL2/SDL.h>

int main(){

  Scene s;
  s.init(660, 440, "test");

  s.run();

  s.suspend();

  std::cout << "Process Terminated..." << "\n";
  return 0;
}
