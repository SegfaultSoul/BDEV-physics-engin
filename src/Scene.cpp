#include "Scene.hpp"
#include "Entity.hpp"


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

void Scene::run(){
  this->running = true;

  while (this->running) {
    //event handelling
    while (SDL_PollEvent(&this->event)) {
      if (this->event.type == SDL_QUIT) {
        this->running = false;
      }
    }

    this->renderer.begin_frame();
    this->renderer.render_all();
    this->renderer.end_frame();
  } 
}
