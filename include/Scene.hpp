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
    double fixed_dt = 1.0 / 60.0; // 60 Hz physics
    double accumulator = 0.0;
    double time_scale = 1.0f;

    void update_dt();

  public:
    void init(int width, int height, std::string title);
    void suspend();
    
    void add_entity(Entity& entity);
    
    void run();

    void set_gravity(const Vector2D<double>& gravity);
    void set_time_scale(double time_scale);
    
    void set_simulation_boundry_criteria(const Vector2D<int>& boundry, const Vector2D<int>& offset, int unit);
};
