#pragma once

#include "core/Chip8.hh"
#include <SDL2/SDL.h>

bool
init(SDL_Window*& window, SDL_Renderer*& renderer, const char* window_title);
void
mainLoop(SDL_Window* window, SDL_Renderer* renderer, chip8::Chip8* chip8);
void
cleanup(SDL_Window* window, SDL_Renderer* renderer);