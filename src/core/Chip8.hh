#ifndef Chip8_HH
#define Chip8_HH

#include "CPU.hh"
#include "Display.hh"
#include "Keyboard.hh"
#include "Memory.hh"
#include "Timers.hh"

namespace chip8
{
    class Chip8
    {
       public:
        Chip8();
        void loadFontSet();
        bool loadROM(const char* filename);
        void cycle();

        [[nodiscard]] const chip8::CPU&      getCPU() const;
        [[nodiscard]] const chip8::Display&  getDisplay() const;
        [[nodiscard]] const chip8::Timers&   getTimer() const;
        [[nodiscard]] const chip8::Memory&   getMemory() const;
        [[nodiscard]] const chip8::Keyboard& getKeyboard() const;

       private:
        chip8::CPU      _cpu;
        chip8::Timers   _timer;
        chip8::Display  _display;
        chip8::Memory   _memory;
        chip8::Keyboard _keyboard;
    };
}  // namespace chip8

#endif  // Chip8_HH