#ifndef CHIP8_CONSTANTS_HH
#define CHIP8_CONSTANTS_HH

#include <cstddef>
#include <cstdint>

namespace chip8
{

    namespace config {
        constexpr std::size_t DISPLAY_X = 64;
        constexpr std::size_t DISPLAY_Y = 32;

        constexpr std::size_t MEMORY_SIZE   = 4096;
        constexpr std::size_t REGISTER_SIZE = 16;
        constexpr std::size_t KEY_SIZE      = 16;
        constexpr std::size_t STACK_SIZE    = 16;

        constexpr std::uint16_t ROM_START_ADDRESS     = 0x200;
        constexpr std::uint16_t FONTSET_START_ADDRESS = 0x50;
    }

}  // namespace chip8::config

#endif  // CHIP8_CONSTANTS_HH
