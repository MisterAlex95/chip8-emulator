// Chip8.hh
#ifndef Chip8_HH
#define Chip8_HH

#include <array>

// Ensure DISPLAY_X and DISPLAY_Y are defined
#ifndef DISPLAY_X
#define DISPLAY_X 64
#endif
#ifndef DISPLAY_Y
#define DISPLAY_Y 32
#endif

#ifndef MEMORY_SIZE
#define MEMORY_SIZE 4096
#endif

#ifndef REGISTER_SIZE
#define REGISTER_SIZE 16
#endif

#ifndef STACK_SIZE
#define STACK_SIZE 16
#endif

#ifndef ROM_START_ADDRESS
#define ROM_START_ADDRESS 0x200
#endif

#ifndef FONTSET_START_ADDRESS
#define FONTSET_START_ADDRESS 0x50
#endif

class Chip8
{
public:
    void initialize();
    void loadFontset();
    bool loadROM(const char *filename);
    void cycle();

    // Display
    const std::array<bool, DISPLAY_Y * DISPLAY_X> getDisplay();
    void setDisplayAt(uint8_t index, bool value);

    // Memory
    const std::array<uint8_t, MEMORY_SIZE> getMemory();
    void setMemoryAt(uint8_t index, uint8_t value);

    // Registers
    const std::array<uint8_t, REGISTER_SIZE> getRegisters();
    const uint16_t getRegisterIndex();
    const uint16_t getRegisterProgramCounter();
    void setRegisterAt(uint8_t index, uint8_t value);
    void setRegisterIndex(uint16_t value);
    void setRegisterProgramCounter(uint16_t value);

    // Stack
    const std::array<uint16_t, STACK_SIZE> getStack();
    void setStackAt(uint8_t index, uint16_t value);

    // Timers
    const uint8_t getDelayTimer();
    const uint8_t getSoundTimer();
    void setDelayTimer(uint8_t value);
    void setSoundTimer(uint8_t value);

private:
    // Memory
    std::array<uint8_t, MEMORY_SIZE> _memory; // 4K memory

    // Registers
    std::array<uint8_t, REGISTER_SIZE> _registers; // 16 registers
    uint16_t _index_register;                      // Index register
    uint16_t _program_counter;                     // Program counter

    // Stack
    std::array<uint16_t, STACK_SIZE> _stack; // Stack for subroutine calls
    uint8_t _stack_pointer;                  // Stack pointer

    // Timers
    uint8_t _delay_timer; // Delay timer
    uint8_t _sound_timer; // Sound timer

    // Input
    uint8_t _keys[16]; // Keypad

    // Display
    std::array<bool, DISPLAY_Y * DISPLAY_X> _display; // 64x32 pixel display
};

#endif // Chip8_HH