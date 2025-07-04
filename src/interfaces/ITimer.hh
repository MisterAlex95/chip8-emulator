#ifndef ITIMER_HH
#define ITIMER_HH

#include <cstdint>

class ITimer
{
   public:
    virtual ~ITimer()                                                 = default;
    virtual void                   waitUntilNextFrame(uint32_t delay) = 0;
    [[nodiscard]] virtual uint32_t getTicks() const                   = 0;
};

#endif  // ITIMER_HH
