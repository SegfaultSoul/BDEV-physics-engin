#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

#include "Renderer.hpp"
#include "Entity.hpp"
#include "EntityVisual.hpp"

void Renderer::init(int width, int height, std::string title){
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (!window)
    std::cerr << "Error initializing window!!!" << "\n";

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer)
    std::cerr << "Error initializing renderer!!!" << "\n";
}

void Renderer::suspend(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// void Renderer::run(){
//     // }

void Renderer::add_entity(Entity entity){
  entity_list.push_back(&entity);
}

void Renderer::render_entity(Entity entity){
  switch (entity.visual.shape) {
    case ShapeType::None:
      break;
    case ShapeType::Rectangel:
      break;
    case ShapeType::Circle:
      break;
  }
}

void Renderer::begin_frame(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Renderer::end_frame(){
  SDL_RenderPresent(renderer);
  SDL_Delay(framerate_delay_ms);
}
