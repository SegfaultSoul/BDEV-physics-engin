#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

#include "Renderer.hpp"

Renderer::Renderer(int width, int height, std::string title){
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (!window)
    std::cerr << "Error initializing window!!!" << "\n";

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer)
    std::cerr << "Error initializing renderer!!!" << "\n";
}

Renderer::~Renderer(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Renderer::run(){
    running = true;

    while (running) {
      //event handelling
      while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
  
    //draw

    SDL_RenderPresent(renderer);
    SDL_Delay(FRAMERATE_MS_DELAY);
  } 
}
