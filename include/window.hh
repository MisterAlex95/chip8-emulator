#pragma once
#include "chip8.hh"
#include <SDL2/SDL.h>

bool init(SDL_Window *&window, SDL_GLContext &gl_context, const char *window_title = nullptr);
void mainLoop(SDL_Window *window, Chip8 *chip8);
void cleanup(SDL_Window *window, SDL_GLContext gl_context);