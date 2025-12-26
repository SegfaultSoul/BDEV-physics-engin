#pragma once

#include "Entity.hpp"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "Vector2D.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Renderer{
  protected:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    bool running = false;
    bool is_grid_rendered = true;

    int framerate_delay_ms = 16;

    std::vector<Entity*> entity_list = {};
    Vector2D<int> window_size = {0, 0};
    Vector2D<int> grid_bounds = {0, 0};
    Vector2D<int> grid_offset = {0, 0};
    int grid_unit = 10;
    SDL_Color color;

    void render_rectangle(Entity* entity);
    void render_circle(Entity* entity);
    void render_grid();


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
    bool get_is_grid_rendered() const;
    void set_is_grid_rendered(bool info);

    Vector2D<int> get_grid_bounds() const;
    void set_grid_bounds(const Vector2D<int>& vec);

    void set_grid_unit(int unit);
    int get_grid_unit() const;
    
    void set_grid_offset(const Vector2D<int>& offset);
    Vector2D<int> get_grid_offset() const;

    Vector2D<int> get_window_size() const;
};
