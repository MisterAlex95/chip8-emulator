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

class Chip8
{
public:
    void initialize();
    bool loadROM(const char *filename);
    void cycle();
    const std::array<bool, DISPLAY_Y * DISPLAY_X> getDisplay();

private:
    static constexpr uint16_t ROM_START_ADDRESS = 0x200;
    static constexpr uint16_t FONTSET_START_ADDRESS = 0x50;

    // Memory
    uint8_t memory[4096]; // 4K memory

    // Registers
    uint8_t V[16]; // 16 registers
    uint16_t I;    // Index register
    uint16_t pc;   // Program counter

    // Stack
    uint16_t stack[16]; // Stack for subroutine calls
    uint8_t sp;         // Stack pointer

    // Timers
    uint8_t delay_timer; // Delay timer
    uint8_t sound_timer; // Sound timer

    // Input
    uint8_t keys[16]; // Keypad

    // Display
    std::array<bool, DISPLAY_Y * DISPLAY_X> display; // 64x32 pixel display

    void loadFontset();
};

#endif // Chip8_HH