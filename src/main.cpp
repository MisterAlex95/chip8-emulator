#include "core/Chip8.hh"
#include "interfaces/IDisplay.hh"
#include "platform/SDL/SDL_Display.hh"
#include "platform/SDL/SDL_Input.hh"
#include "platform/SDL/SDL_Keyboard.hh"
#include "platform/SDL/SDL_Timer.hh"
#include "window.hh"

#ifdef DEV_MODE
#include <iostream>
#endif

int
main(int argc, char** argv)
{
#ifdef DEV_MODE
    std::cout << "[DEBUG MODE] with " << argc << " arguments\n";
#endif

    auto display  = SDL::SDL_Display(10);
    auto input    = SDL::SDL_Input();
    auto timer    = SDL::SDL_Timer();
    auto keyboard = new SDL::SDL_Keyboard();
    auto chip8    = new chip8::Chip8(keyboard);

    chip8->loadFontSet();

    if (chip8->loadROM(argv[1]))
    {
        mainLoop(chip8, input, display, timer);
    }

    return 0;
}