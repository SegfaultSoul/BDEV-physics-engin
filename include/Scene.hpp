#pragma once

#include "Entity.hpp"
#include "PhysicsEngin.hpp"
#include "Renderer.hpp"
#include "SDL_events.h"
#include <vector>

class Scene {
  protected:
    std::vector<Entity> entity_list = {};
    bool running = false;
    Renderer renderer;
    PhysicsEngin physics_engin;

    SDL_Event event;

  public:
    void init(int width, int height, std::string title);
    void suspend();

    void add_entity(Entity& entity);
    
    void run();
};
