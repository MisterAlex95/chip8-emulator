// Chip8.hh
#ifndef Chip8_HH
#define Chip8_HH

#include <array>

#include "Constants.hh"
#include "Timers.hh"

namespace chip8
{

    class Chip8
    {
       public:
        void initialize();
        void loadFontset();
        bool loadROM(const char* filename);
        void cycle();

        // Display
        [[nodiscard]] const std::array<bool, chip8::config::DISPLAY_Y * chip8::config::DISPLAY_X>&
             getDisplay() const;
        void setDisplayAt(std::size_t index, bool value);

        // Memory
        [[nodiscard]] const std::array<uint8_t, chip8::config::MEMORY_SIZE>& getMemory() const;
        void setMemoryAt(std::size_t index, uint8_t value);

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

        // Timers
        [[nodiscard]] const chip8::Timers& getTimer() const;

       private:
        // Memory
        std::array<uint8_t, chip8::config::MEMORY_SIZE> _memory;  // 4K memory

        // Registers
        std::array<uint8_t, chip8::config::REGISTER_SIZE> _registers;        // 16 registers
        uint16_t                                          _index_register;   // Index register
        uint16_t                                          _program_counter;  // Program counter

        // Stack
        std::array<uint16_t, chip8::config::STACK_SIZE> _stack;  // Stack for subroutine calls
        uint8_t                                         _stack_pointer;  // Stack pointer

        chip8::Timers _timer;

        // Input
        std::array<uint8_t, chip8::config::KEY_SIZE> _keys;  // Keypad

        // Display
        std::array<bool, chip8::config::DISPLAY_Y * chip8::config::DISPLAY_X>
            _display;  // 64x32 pixel display
    };
}  // namespace chip8

#endif  // Chip8_HH