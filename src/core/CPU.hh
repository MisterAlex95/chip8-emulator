#ifndef CHIP8_CPU_HH
#define CHIP8_CPU_HH

#include "Display.hh"
#include "Keyboard.hh"
#include "Memory.hh"
#include "Timers.hh"
#include "Types.hh"
#include <cstdint>

namespace chip8
{

    class CPU
    {
       public:
        explicit CPU(Memory& mem, Display& disp, Timers& timers, Keyboard& keys);

        void cycle();  // une instruction

       private:
        // Références vers les modules
        Memory&   _memory;
        Display&  _display;
        Timers&   _timers;
        Keyboard& _keyboard;

        // Registres internes
        std::array<uint8_t, config::REGISTER_SIZE> _V{};
        uint16_t                                   _I  = 0;
        uint16_t                                   _PC = config::ROM_START_ADDRESS;
        std::array<uint16_t, config::STACK_SIZE>   _stack{};
        uint8_t                                    _SP = 0;

        // Méthodes utilitaires internes
        uint16_t fetchOpcode() const;
        void     executeOpcode(uint16_t opcode);

        // Décodeurs spécialisés (optionnel)
        void decode0(uint16_t opcode);
        void decode8(uint16_t opcode);
        void decodeE(uint16_t opcode);
        void decodeF(uint16_t opcode);
    };

}  // namespace chip8

#endif  // CHIP8_CPU_HH
