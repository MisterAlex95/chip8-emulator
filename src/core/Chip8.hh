#ifndef Chip8_HH
#define Chip8_HH

#include "CPU.hh"
#include "Display.hh"
#include "Memory.hh"
#include "Timers.hh"
#include "interfaces/IKeyboard.hh"

namespace chip8
{
    class Chip8
    {
       public:
        explicit Chip8(chip8::IKeyboard* keyboard);
        void loadFontSet();
        bool loadROM(const char* filename);
        void cycle();

        [[nodiscard]] const chip8::CPU&       getCPU() const;
        [[nodiscard]] const chip8::Display&   getDisplay() const;
        [[nodiscard]] const chip8::Timers&    getTimer() const;
        [[nodiscard]] const chip8::Memory&    getMemory() const;
        [[nodiscard]] const chip8::IKeyboard& getKeyboard() const;

       private:
        CPU               _cpu;
        chip8::Timers     _timer;
        chip8::Display    _display;
        chip8::Memory     _memory;
        chip8::IKeyboard* _keyboard;
    };
}  // namespace chip8

#endif  // Chip8_HH