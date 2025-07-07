#pragma once

#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Renderer{
  protected:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    bool running = false;

    int framerate_delay_ms = 16;

    std::vector<Entity*> entity_list = {};

  public:
    void init(int width, int height, std::string title);
    void suspend();

    // void run();
    void add_entity(Entity entity); 
    void render_entity(Entity entity);
    
    void begin_frame();
    void end_frame();

    // void render_entities();
};
