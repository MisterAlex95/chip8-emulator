#include "Timers.hh"

chip8::Timers::Timers() : delay_timer(0), sound_timer(0) {}

void
chip8::Timers::reset()
{
    delay_timer = 0;
    sound_timer = 0;
}

void
chip8::Timers::tick()
{
    if (delay_timer > 0)
        --delay_timer;

    if (sound_timer > 0)
        --sound_timer;
}

void
chip8::Timers::set_delay(uint8_t value)
{
    delay_timer = value;
}

void
chip8::Timers::set_sound(uint8_t value)
{
    sound_timer = value;
}

[[nodiscard]] uint8_t
chip8::Timers::get_delay() const
{
    return delay_timer;
}

[[nodiscard]] uint8_t
chip8::Timers::get_sound() const
{
    return sound_timer;
}

bool
chip8::Timers::is_beeping() const
{
    return sound_timer > 0;
}
