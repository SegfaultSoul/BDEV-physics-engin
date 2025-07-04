#pragma once

#include <SDL2/SDL.h>
#include <string>

class Renderer{
  protected:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    bool running = false;

    const int FRAMERATE_MS_DELAY = 16;

  public:
    Renderer(int width, int height, std::string title);
    ~Renderer();

    void run();

};
