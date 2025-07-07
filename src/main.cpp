#include "Renderer.hpp"
#include "SDL_events.h"
#include <iostream>
#include <SDL2/SDL.h>

int main(){
  Renderer r;
  r.init(640, 440, "Test");

  bool running = true;
  SDL_Event event;

  while (running) {
    //event handelling
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    r.begin_frame();

    r.end_frame();
  } 

  r.suspend();
  std::cout << "Process Terminated..." << "\n";
  return 0;
}
