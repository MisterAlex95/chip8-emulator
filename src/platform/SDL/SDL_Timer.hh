#ifndef SDL_TIMER_HH
#define SDL_TIMER_HH

#include "interfaces/ITimer.hh"

#include <cstdint>

namespace SDL
{
    class SDL_Timer : public ITimer
    {
       public:
        void                   waitUntilNextFrame(uint32_t delay) override;
        [[nodiscard]] uint32_t getTicks() const override;
    };
}  // namespace SDL

#endif  // SDL_TIMER_HH
