
#include "CPU.hh"

#include <iostream>

chip8::CPU::CPU(chip8::Memory* mem, chip8::Display* disp, chip8::Timers* timers,
                chip8::IKeyboard* keys)
    : _memory(mem), _display(disp), _timers(timers), _keyboard(keys)
{
}

void
chip8::CPU::cycle()
{
    auto opcode = fetchOpcode();
    this->_program_counter += 2;

    switch (opcode & 0xF000)
    {
        case 0x0000:
            this->decode0(opcode);
            break;

        case 0x1000:  // JP addr
        {
            this->decode1(opcode);
            break;
        }

        case 0xD000:  // DRW Vx, Vy, nibble
        {
            this->decodeD(opcode);
            break;
        }

        default:
            std::cerr << "[Warning] Unhandled opcode: 0x" << std::hex << opcode << std::dec << "\n";
            break;
    }

    this->_timers->tick();
}

uint16_t
chip8::CPU::fetchOpcode() const
{
    if (this->_program_counter + 1 >= _memory->getSize())
    {
        std::cerr << "[Error] Program counter out of memory bounds\n";
        throw std::runtime_error("[Error] Program counter out of memory bounds");
    }

    const uint16_t opcode =
        static_cast<uint16_t>(_memory->getMemoryAt(this->_program_counter) << 8) |
        _memory->getMemoryAt(this->_program_counter + 1);
    return opcode;
}

void
chip8::CPU::decode0(uint16_t opcode)
{
    switch (opcode & 0x00FF)
    {
        case 0x00E0:  // CLS
            _display->clean();
            break;

        case 0x00EE:  // RET
            if (this->_stack_pointer == 0)
            {
                std::cerr << "[Error] Return with empty stack\n";
                break;
            }
            --this->_stack_pointer;
            this->_program_counter = _stack[this->_stack_pointer];
            break;

        default:
            std::cerr << "[Warning] Unknown opcode: 0x" << std::hex << opcode << std::dec << "\n";
            break;
    }
}

void
chip8::CPU::decode1(uint16_t opcode)
{
    const uint16_t address = opcode & 0x0FFF;
    this->_program_counter = address;
}

void
chip8::CPU::decode8(uint16_t opcode)
{
}

void
chip8::CPU::decodeD(uint16_t opcode)
{
    const uint8_t x      = (opcode & 0x0F00) >> 8;
    const uint8_t y      = (opcode & 0x00F0) >> 4;
    const uint8_t height = opcode & 0x000F;

    this->_registers[0xF] = 0;

    for (uint8_t row = 0; row < height; ++row)
    {
        const uint8_t spriteByte = _memory->getMemoryAt(this->_index_register + row);
        for (uint8_t col = 0; col < 8; ++col)
        {
            const bool spritePixel = (spriteByte & (0x80 >> col)) != 0;
            if (spritePixel)
            {
                const uint16_t pixelX = (this->_registers[x] + col) % chip8::config::DISPLAY_X;
                const uint16_t pixelY = (this->_registers[y] + row) % chip8::config::DISPLAY_Y;

                if (_display->isPixelEnable(pixelY, pixelX))
                    this->_registers[0xF] = 1;

                _display->setDisplayAt(pixelY, pixelX,
                                       _display->isPixelEnable(pixelY, pixelX) ^ true);
            }
        }
    }
}

void
chip8::CPU::decodeE(uint16_t opcode)
{
}

void
chip8::CPU::decodeF(uint16_t opcode)
{
}