
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

    //    std::cout << std::hex << "[FETCH] PC=" << _program_counter << " OPCODE=0x" << opcode <<
    //    std::dec
    //            << "\n";

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

        case 0x2000:  //
        {
            this->decode2(opcode);
            break;
        }

        case 0x3000:  //
        {
            this->decode3(opcode);
            break;
        }

        case 0x4000:  //
        {
            this->decode4(opcode);
            break;
        }

        case 0x5000:  //
        {
            this->decode5(opcode);
            break;
        }

        case 0x6000:
        {
            this->decode6(opcode);
            break;
        }

        case 0x7000:
        {
            this->decode7(opcode);
            break;
        }

        case 0x8000:
        {
            this->decode8(opcode);
            break;
        }

        case 0x9000:
        {
            this->decode9(opcode);
            break;
        }

        case 0xA000:  //
        {
            this->decodeA(opcode);
            break;
        }

        case 0xD000:  // DRW Vx, Vy, nibble
        {
            this->decodeD(opcode);
            break;
        }

        case 0xE000:
        {
            this->decodeE(opcode);
            break;
        }

        case 0xF000:
        {
            this->decodeF(opcode);
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
            _display->clear();
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
chip8::CPU::decode1(uint16_t opcode)  // 1nnn
{
    const uint16_t address = opcode & 0x0FFF;
    this->_program_counter = address;
}

void
chip8::CPU::decode2(uint16_t opcode)  // 2NNN
{
    const uint16_t address   = opcode & 0x0FFF;
    _stack[_stack_pointer++] = _program_counter;
    _program_counter         = address;
}

void
chip8::CPU::decode3(uint16_t opcode)  // 3xkk
{
    const uint8_t x  = (opcode & 0x0F00) >> 8;
    const uint8_t kk = opcode & 0x00FF;

    if (this->_registers[x] == kk)
    {
        this->_program_counter += 2;
    }
}

void
chip8::CPU::decode4(uint16_t opcode)  // 4xkk
{
    const uint8_t x  = (opcode & 0x0F00) >> 8;
    const uint8_t kk = opcode & 0x00FF;

    if (this->_registers[x] != kk)
    {
        this->_program_counter += 2;
    }
}

void
chip8::CPU::decode5(uint16_t opcode)  // 5xy0
{
    const uint8_t x = (opcode & 0x0F00) >> 8;
    const uint8_t y = opcode & 0x00F0 >> 4;

    if (this->_registers[x] == y)
    {
        this->_program_counter += 2;
    }
}

void
chip8::CPU::decode6(uint16_t opcode)  // 6xkk
{
    const uint8_t x     = (opcode & 0x0F00) >> 8;
    const uint8_t kk    = opcode & 0x00FF;
    this->_registers[x] = kk;
}

void
chip8::CPU::decode7(uint16_t opcode)  // 7xkk
{
    const uint8_t x  = (opcode & 0x0F00) >> 8;
    const uint8_t kk = opcode & 0x00FF;
    this->_registers[x] += kk;
}

void
chip8::CPU::decode8(uint16_t opcode)
{
}

void
chip8::CPU::decode9(uint16_t opcode)  // 9xy0
{
    const uint8_t x = (opcode & 0x0F00) >> 8;
    const uint8_t y = opcode & 0x00F0 >> 4;

    if (this->_registers[x] != y)
    {
        this->_program_counter += 2;
    }
}

void
chip8::CPU::decodeA(uint16_t opcode)  // Annn
{
    _index_register = opcode & 0x0FFF;
}

void
chip8::CPU::decodeD(uint16_t opcode)  // Dxyn
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
            bool spritePixel = (spriteByte & (0x80 >> col)) != 0;

            if (spritePixel)
            {
                const uint16_t pixelX = (this->_registers[x] + col) % chip8::config::DISPLAY_X;
                const uint16_t pixelY = (this->_registers[y] + row) % chip8::config::DISPLAY_Y;

                bool pixelBefore = _display->isPixelEnable(pixelX, pixelY);
                bool pixelAfter  = pixelBefore ^ true;  // XOR toggle

                _display->setDisplayAt(pixelX, pixelY, pixelAfter);

                if (pixelBefore && !pixelAfter)
                    this->_registers[0xF] = 1;
            }
        }
    }
}

void
chip8::CPU::decodeE(uint16_t opcode)
{
    const uint8_t x   = (opcode & 0x0F00) >> 8;
    const uint8_t key = _registers[x];

    switch (opcode & 0x00FF)
    {
        case 0x9E:  // Ex9E
            if (_keyboard->isKeyPressed(key))
            {
                _program_counter += 2;
            }
            break;
        case 0xA1:  // ExA1
            if (!_keyboard->isKeyPressed(key))
            {
                _program_counter += 2;
            }
            break;
        default:
            std::cerr << "[Warning] Unknown opcode: 0x" << std::hex << opcode << std::dec << "\n";
            break;
    }
}

void
chip8::CPU::decodeF(uint16_t opcode)
{
    const uint8_t x        = (opcode & 0x0F00) >> 8;
    const uint8_t lastByte = opcode & 0x00FF;

    switch (lastByte)
    {
        case 0x07:  // FX07: Set Vx = delay timer
            _registers[x] = _timers->get_delay();
            break;

        case 0x15:  // FX15: Set delay timer = Vx
            _timers->set_delay(_registers[x]);
            break;

        case 0x1E:  // FX1E: I = I + Vx
            _index_register += _registers[x];
            break;

        case 0x29:  // FX29: Set I to location of sprite for digit in Vx
            _index_register = chip8::config::FONTSET_START_ADDRESS + (_registers[x] * 5);
            break;

        case 0x33:  // FX33: Store BCD of Vx at I, I+1, I+2
        {
            uint8_t value = _registers[x];
            _memory->setMemoryAt(_index_register, value / 100);
            _memory->setMemoryAt(_index_register + 1, (value / 10) % 10);
            _memory->setMemoryAt(_index_register + 2, value % 10);
            break;
        }

        case 0x65:  // FX65: Read registers V0 through Vx from memory starting at I
            for (int i = 0; i <= x; ++i) _registers[i] = _memory->getMemoryAt(_index_register + i);
            break;

        case 0x55:  // FX55: Store V0 through Vx in memory starting at I
            for (int i = 0; i <= x; ++i) _memory->setMemoryAt(_index_register + i, _registers[i]);
            break;

        case 0x0A:  // FX0A: Wait for key press, store in Vx
        {
            bool keyPressed = false;
            for (uint8_t i = 0; i < 16; ++i)
            {
                if (_keyboard->isKeyPressed(i))
                {
                    _registers[x] = i;
                    keyPressed    = true;
                    break;
                }
            }

            if (!keyPressed)
            {
                // Ne pas avancer le PC, on attend encore une touche
                _program_counter -= 2;  // recule PC pour réexécuter l'instruction
            }
            break;
        }

        default:
            std::cerr << "[Warning] Unhandled FX__ opcode: 0x" << std::hex << opcode << std::dec
                      << "\n";
            break;
    }
}
