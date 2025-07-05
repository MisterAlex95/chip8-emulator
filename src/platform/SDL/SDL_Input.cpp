#include "SDL_Input.hh"
#include "SDL_Keyboard.hh"

#include <SDL_events.h>

namespace SDL
{
    void SDL_Input::pollEvents(chip8::IKeyboard* keyboard, bool& quitFlag)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quitFlag = false;

            else if (event.type == SDL_KEYDOWN)
            {
                auto key = SDL::SDL_Keyboard::mapSDLKey(event.key.keysym.sym);
                if (key.has_value())
                {
                    auto k   = key.value();
                    auto evt = chip8::Event(chip8::Event::Type::KeyDown, k);
                    keyboard->handleEvent(evt);
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                auto key = SDL::SDL_Keyboard::mapSDLKey(event.key.keysym.sym);
                if (key.has_value())
                {
                    auto k   = key.value();
                    auto evt = chip8::Event(chip8::Event::Type::KeyUp, k);
                    keyboard->handleEvent(evt);
                }
            }
        }
    }
}  // namespace SDL
