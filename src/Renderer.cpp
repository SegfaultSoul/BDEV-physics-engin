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

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
  switch (entity->get_shape()) {
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
  if (this->is_grid_rendered) {
    this->render_grid();
  }
  for (Entity* entity : this->entity_list) {
    this->render_entity(entity);
  }
}

void Renderer::render_rectangle(Entity* entity){
  Vector2D<double> pos = entity->get_body()->get_position();
  Vector2D<double> size = entity->get_visual()->get_size();
    
  this->set_draw_color(entity->get_visual()->get_color());

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

void Renderer::render_grid() {
  this->set_draw_color({32, 32, 32, 255});

  for (int x = 0; x <= this->grid_bounds.x; x+=this->grid_unit)
    SDL_RenderDrawLine(this->renderer, this->grid_offset.x + x, this->grid_offset.y, this->grid_offset.x + x, this->grid_offset.y + this->grid_bounds.y);
    
  for (int y = 0; y <= this->grid_bounds.y; y+=this->grid_unit)
    SDL_RenderDrawLine(this->renderer, this->grid_offset.x, this->grid_offset.y + y, this->grid_offset.x + this->grid_bounds.x, this->grid_offset.y + y);
}

bool Renderer::get_is_grid_rendered() const {
  return this->is_grid_rendered;
}

void Renderer::set_is_grid_rendered(bool info) {
  this->is_grid_rendered = info;
}

Vector2D<int> Renderer::get_grid_bounds() const {
  return this->grid_bounds;
}

void Renderer::set_grid_bounds(const Vector2D<int>& vec) {
  this->grid_bounds = vec;
}

void Renderer::set_grid_unit(int unit) {
  this->grid_unit = unit; 
}

int Renderer::get_grid_unit() const {
  return this->grid_unit; 
}

void Renderer::set_grid_offset(const Vector2D<int>& offset) {
  this->grid_offset = offset;
}

Vector2D<int> Renderer::get_grid_offset() const {
  return this->grid_offset;
}
