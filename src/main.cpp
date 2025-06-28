#include "window.hh"
#include "utils.hh"
#include "core/Chip8.hh"
#include <iostream>

using namespace chip8;

int main(int argc, char **argv)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer;

    if (!init(window, renderer, "chip8 emulator"))
        sdlFail("Erreur d'initialisation SDL/OpenGL");

    Chip8 *chip8 = new Chip8();
    chip8->initialize();
    chip8->loadFontset();

    bool isLoaded = chip8->loadROM(argv[1]);

    if (isLoaded)
    {
        mainLoop(window, renderer, chip8);
    }

    cleanup(window, renderer);

    return 0;
}