#include "SDL_Timer.hh"

#include <SDL_timer.h>

namespace SDL
{
    void SDL_Timer::waitUntilNextFrame(uint32_t delay)
    {
        SDL_Delay(delay);
    }

    uint32_t SDL_Timer::getTicks() const
    {
        return SDL_GetTicks();
    }

}  // namespace SDL
