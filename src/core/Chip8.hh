#ifndef Chip8_HH
#define Chip8_HH

#include "CPU.hh"
#include "Display.hh"
#include "Memory.hh"
#include "Timers.hh"
#include "interfaces/IDisplay.hh"
#include "interfaces/IInput.hh"
#include "interfaces/IKeyboard.hh"
#include "interfaces/ITimer.hh"

namespace chip8
{
    class Chip8
    {
       public:
        explicit Chip8(chip8::IKeyboard* keyboard);
        void loadFontSet();
        bool loadROM(const char* filename);
        void cycle();

        [[nodiscard]] chip8::CPU*       getCPU() const;
        [[nodiscard]] chip8::Display*   getDisplay() const;
        [[nodiscard]] chip8::Timers*    getTimer() const;
        [[nodiscard]] chip8::Memory*    getMemory() const;
        [[nodiscard]] chip8::IKeyboard* getKeyboard() const;

       private:
        std::unique_ptr<chip8::CPU>     _cpu;
        std::unique_ptr<chip8::Memory>  _memory;
        std::unique_ptr<chip8::Timers>  _timer;
        std::unique_ptr<chip8::Display> _display;
        std::unique_ptr<IKeyboard>      _keyboard;
    };
}  // namespace chip8

#endif  // Chip8_HH