#ifndef Chip8_HH
#define Chip8_HH

#include <array>

#include "Constants.hh"
#include "Timers.hh"
#include "Memory.hh"
#include "Display.hh"

namespace chip8
{

    class Chip8
    {
       public:
        Chip8();
        void initialize();
        void loadFontset();
        bool loadROM(const char* filename);
        void cycle();

        // Registers
        [[nodiscard]] const std::array<uint8_t, chip8::config::REGISTER_SIZE>& getRegisters() const;
        [[nodiscard]] uint16_t getRegisterIndex() const;
        [[nodiscard]] uint16_t getRegisterProgramCounter() const;
        void                   setRegisterAt(std::size_t index, uint8_t value);
        void                   setRegisterIndex(uint16_t value);
        void                   setRegisterProgramCounter(uint16_t value);

        // Stack
        [[nodiscard]] const std::array<uint16_t, chip8::config::STACK_SIZE>& getStack() const;
        void setStackAt(std::size_t index, uint16_t value);

        [[nodiscard]] const chip8::Display& getDisplay() const;
        [[nodiscard]] const chip8::Timers& getTimer() const;
        [[nodiscard]] const chip8::Memory& getMemory() const;

       private:
        // Registers
        std::array<uint8_t, chip8::config::REGISTER_SIZE> _registers;        // 16 registers
        uint16_t                                          _index_register;   // Index register
        uint16_t                                          _program_counter;  // Program counter

        // Stack
        std::array<uint16_t, chip8::config::STACK_SIZE> _stack;  // Stack for subroutine calls
        uint8_t                                         _stack_pointer;  // Stack pointer

        chip8::Timers _timer;
        chip8::Display _display;
        chip8::Memory _memory;

        // Input
        std::array<uint8_t, chip8::config::KEY_SIZE> _keys;  // Keypad
    };
}  // namespace chip8

#endif  // Chip8_HH