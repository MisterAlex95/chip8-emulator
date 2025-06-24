#include "utils.hh"
#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>

void sdlFail(const char *message)
{
    std::cerr << message << "\n";
    SDL_Quit();
    exit(-1);
}