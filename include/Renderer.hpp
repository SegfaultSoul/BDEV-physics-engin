#pragma once

#include "Entity.hpp"
#include "SDL_pixels.h"
#include "SDL_render.h"
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

    SDL_Color color;

  private:
    void render_rectangle(Entity* entity);
    void render_circle();


  public:
    void init(int width, int height, std::string title);
    void suspend();

    // void run();
    void add_entity(Entity* entity); 
    void render_entity(Entity* entity);
    
    void begin_frame();
    void end_frame();

    void set_draw_color(SDL_Color);

    void render_all();  
  
};
