#ifndef TIMERS_HH
#define TIMERS_HH

#include <cstdint>

namespace chip8
{
    class Timers
    {
       public:
        Timers();

        void reset();

        void tick();  // Appelé à 60 Hz : décrémente les timers

        void set_delay(uint8_t value);
        void set_sound(uint8_t value);

        [[nodiscard]] uint8_t get_delay() const;
        [[nodiscard]] uint8_t get_sound() const;

        bool is_beeping() const;  // true si sound_timer > 0

       private:
        uint8_t delay_timer;
        uint8_t sound_timer;
    };

}  // namespace chip8

#endif  // TIMERS_HH
