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
        explicit CPU(chip8::Memory* mem, chip8::Display* disp, chip8::Timers* timers,
                     chip8::IKeyboard* keys);

        void cycle();

       private:
        Memory*    _memory;
        Display*   _display;
        Timers*    _timers;
        IKeyboard* _keyboard;

        RegisterArray _registers{};  // V
        uint16_t      _index_register  = 0;
        uint16_t      _program_counter = config::ROM_START_ADDRESS;
        StackArray    _stack{};
        uint8_t       _stack_pointer = 0;

        uint16_t fetchOpcode() const;
        void     executeOpcode(uint16_t opcode);

        // Décodeurs spécialisés (optionnel)
        void decode0(uint16_t opcode);
        void decode1(uint16_t opcode);
        void decode2(uint16_t opcode);
        void decode3(uint16_t opcode);
        void decode4(uint16_t opcode);
        void decode6(uint16_t opcode);
        void decode7(uint16_t opcode);
        void decode8(uint16_t opcode);
        void decodeD(uint16_t opcode);
        void decodeE(uint16_t opcode);
        void decodeF(uint16_t opcode);
    };

}  // namespace chip8

#endif  // CHIP8_CPU_HH
