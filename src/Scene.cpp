#include "Scene.hpp"
#include "Entity.hpp"
#include "SDL_stdinc.h"
#include "Vector2D.hpp"

void Scene::init(int width, int height, std::string title, bool render_grid){
  this->renderer.init(width, height, title);
  this->renderer.set_is_grid_rendered(render_grid);
}

void Scene::suspend(){
  this->renderer.suspend();
}

void Scene::add_entity(Entity& entity){
  this->entity_list.push_back(entity);
  this->renderer.add_entity(&entity_list.back());
  this->physics_engin.add_entity(&entity_list.back());
}

void Scene::update_dt(){
  Uint32 current_time = SDL_GetTicks();
  double frame_dt = (current_time - this->last_time) / 1000.0f;
  this->last_time = current_time;

  if (frame_dt > 0.25) frame_dt = 0.25;

  this->accumulator += frame_dt * this->time_scale;
}

void Scene::run(){
  this->running = true;
  this->last_time = SDL_GetTicks();

  while (this->running) {
    //event handelling
    while (SDL_PollEvent(&this->event)) {
      if (this->event.type == SDL_QUIT) {
        this->running = false;
      }
    }

    this->update_dt();
    while (this->accumulator >= this->fixed_dt) {
      this->physics_engin.update(this->fixed_dt);
      this->accumulator -= this->fixed_dt;
    }

    this->renderer.begin_frame();
    this->renderer.render_all();
    this->renderer.end_frame();
  } 
}

void Scene::set_gravity(const Vector2D<double>& gravity) {
  this->physics_engin.set_gravity(gravity);
}

void Scene::set_time_scale(double time_scale) {
  this->time_scale = time_scale;
}

void Scene::set_simulation_boundry_criteria(const Vector2D<int>& boundry, int unit) {
  physics_engin.set_boundry(boundry);
  renderer.set_grid_bounds(boundry);

  renderer.set_grid_unit(unit);

  Vector2D<int> offset = (renderer.get_window_size() - boundry) / 2;

  physics_engin.set_bounds_offset(offset);
  renderer.set_grid_offset(offset);
}

