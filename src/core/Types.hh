#ifndef CHIP8_TYPES_HH
#define CHIP8_TYPES_HH

#include <array>
#include <cstdint>

#include "Constants.hh"  // pour les tailles comme MEMORY_SIZE, REGISTER_SIZE...

namespace chip8
{

    // Alias explicites pour les structures de base

    using MemoryArray   = std::array<std::uint8_t, config::MEMORY_SIZE>;
    using RegisterArray = std::array<std::uint8_t, config::REGISTER_SIZE>;
    using StackArray    = std::array<std::uint16_t, config::STACK_SIZE>;
    using DisplayArray  = std::array<bool, config::DISPLAY_X * config::DISPLAY_Y>;
    using KeypadArray   = std::array<std::uint8_t, 16>;  // clavier 0x0 à 0xF

    // Enumérations possibles pour lisibilité (optionnel)
    enum class Key : std::uint8_t
    {
        Num0 = 0x0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        NumA,
        NumB,
        NumC,
        NumD,
        NumE,
        NumF
    };

}  // namespace chip8

#endif  // CHIP8_TYPES_HH
