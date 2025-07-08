#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

#include "Renderer.hpp"
#include "Entity.hpp"
#include "EntityVisual.hpp"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "Vector2D.hpp"

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

void Renderer::add_entity(Entity* entity){
  entity_list.push_back(entity);
}

//TODO: Fix
void Renderer::render_entity(Entity* entity){
  switch (entity->visual.get_shape()) {
    case ShapeType::None :
      break;
    case ShapeType::Circle :
      break;
    case ShapeType::Rectangle :
      this->render_rectangle(entity);
      break;
  }
}

void Renderer::render_all(){
  for (Entity* entity : this->entity_list) {
    this->render_entity(entity);
  }
}

void Renderer::render_rectangle(Entity* entity){
  Vector2D<double> pos = entity->body.get_position();
  Vector2D<double> size = entity->visual.get_size();
    
  this->set_draw_color(entity->visual.get_color());

  const SDL_Rect rect = {
    static_cast<int>(std::round(pos.x - size.x / 2)), 
    static_cast<int>(std::round(pos.y - size.y /2)), 
    static_cast<int>(std::round(size.x)), 
    static_cast<int>(std::round(size.y))
  };

  SDL_RenderFillRect(this->renderer, &rect);
}

void Renderer::begin_frame(){
  this->set_draw_color({0, 0, 0, 255});
  SDL_RenderClear(renderer);
}

void Renderer::end_frame(){
  SDL_RenderPresent(renderer);
  SDL_Delay(framerate_delay_ms);
}

void Renderer::set_draw_color(SDL_Color color){
  this->color = color;
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

