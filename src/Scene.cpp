#include "Scene.hpp"
#include "Entity.hpp"
#include "SDL_stdinc.h"


void Scene::init(int width, int height, std::string title){
  this->renderer.init(width, height, title);
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
  this->dt = (current_time - this->last_time) / 1000.0f;
  this->last_time = current_time;
}

void Scene::run(){
  this->running = true;

  while (this->running) {
    this->update_dt();

    //event handelling
    while (SDL_PollEvent(&this->event)) {
      if (this->event.type == SDL_QUIT) {
        this->running = false;
      }
    }

    this->physics_engin.update(dt);

    this->renderer.begin_frame();
    this->renderer.render_all();
    this->renderer.end_frame();
  } 
}

void Scene::set_gravity(const Vector2D<double>& gravity) {
  this->physics_engin.set_gravity(gravity);
}
