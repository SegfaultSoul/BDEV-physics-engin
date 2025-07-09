#pragma once

#include "Entity.hpp"
#include "PhysicsEngin.hpp"
#include "Renderer.hpp"
#include "SDL_events.h"
#include "SDL_stdinc.h"
#include "Vector2D.hpp"
#include <vector>

class Scene {
  protected:
    std::vector<Entity> entity_list = {};
    bool running = false;
    Renderer renderer;
    PhysicsEngin physics_engin;

    SDL_Event event;

    Uint32 last_time = 0;
    double dt = 0.0f;
    double time_scale = 1.0f;

    void update_dt();

  public:
    void init(int width, int height, std::string title);
    void suspend();

    void add_entity(Entity& entity);
    
    void run();

    void set_gravity(const Vector2D<double>& gravity);
    void set_time_scale(double time_scale);
};
