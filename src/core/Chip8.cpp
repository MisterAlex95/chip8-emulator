#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "Chip8.hh"
#include "Constants.hh"
#include "Fontset.hh"
#include "Timers.hh"

chip8::Chip8::Chip8()
{
    _timer = new chip8::Timers();
}

void
chip8::Chip8::initialize()
{
    _memory.fill(0);
    _registers.fill(0);
    _index_register  = 0;
    _program_counter = chip8::config::ROM_START_ADDRESS;

    _stack.fill(0);
    _stack_pointer = 0;

    _keys.fill(0);
    _display.fill(false);
}

void
chip8::Chip8::loadFontset()
{
    for (size_t i = 0; i < chip8::CHIP8_FONTSET_SIZE; ++i)
    {
        _memory[chip8::config::FONTSET_START_ADDRESS + i] = chip8::CHIP8_FONTSET[i];
    }
}

bool
chip8::Chip8::loadROM(const char* filename)
{
    if (!filename)
    {
        std::cerr << "[Error] Filename is empty\n";
        return false;
    }

    std::cout << "Loading ROM: " << filename << std::endl;

    std::ifstream romFile(filename, std::ios::binary);
    if (!romFile.is_open())
    {
        std::cerr << "[Error] Unable to open ROM file\n";
        return false;
    }

    romFile.seekg(0, std::ios::end);
    std::streamsize size = romFile.tellg();
    romFile.seekg(0, std::ios::beg);

    if (size <= 0)
    {
        std::cerr << "[Error] ROM file is empty or unreadable\n";
        return false;
    }

    if (chip8::config::ROM_START_ADDRESS + size > _memory.size())
    {
        std::cerr << "[Error] ROM size exceeds memory capacity\n";
        return false;
    }

    if (!romFile.read(reinterpret_cast<char*>(&_memory[chip8::config::ROM_START_ADDRESS]), size))
    {
        std::cerr << "[Error] Failed to read ROM into memory\n";
        return false;
    }

    std::cout << "ROM loaded successfully (" << size << " bytes)\n";
    return true;
}

void
chip8::Chip8::cycle()
{
    // === FETCH ===
    if (_program_counter + 1 >= _memory.size())
    {
        std::cerr << "[Error] Program counter out of memory bounds\n";
        return;
    }

    const uint16_t opcode =
        static_cast<uint16_t>(_memory[_program_counter] << 8) | _memory[_program_counter + 1];
    _program_counter += 2;  // avance par défaut

    // === DECODE & EXECUTE ===
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
                case 0x00E0:  // CLS
                    _display.fill(false);
                    break;

                case 0x00EE:  // RET
                    if (_stack_pointer == 0)
                    {
                        std::cerr << "[Error] Return with empty stack\n";
                        break;
                    }
                    --_stack_pointer;
                    _program_counter = _stack[_stack_pointer];
                    break;

                default:
                    std::cerr << "[Warning] Unknown opcode: 0x" << std::hex << opcode << std::dec
                              << "\n";
                    break;
            }
            break;

        case 0x1000:  // JP addr
        {
            const uint16_t address = opcode & 0x0FFF;
            _program_counter       = address;
            break;
        }

        case 0xD000:  // DRW Vx, Vy, nibble
        {
            const uint8_t x      = (opcode & 0x0F00) >> 8;
            const uint8_t y      = (opcode & 0x00F0) >> 4;
            const uint8_t height = opcode & 0x000F;

            _registers[0xF] = 0;

            for (uint8_t row = 0; row < height; ++row)
            {
                const uint8_t spriteByte = _memory[_index_register + row];
                for (uint8_t col = 0; col < 8; ++col)
                {
                    const bool spritePixel = (spriteByte & (0x80 >> col)) != 0;
                    if (spritePixel)
                    {
                        const uint16_t pixelX = (_registers[x] + col) % chip8::config::DISPLAY_X;
                        const uint16_t pixelY = (_registers[y] + row) % chip8::config::DISPLAY_Y;
                        const uint16_t pixelIndex = pixelY * chip8::config::DISPLAY_X + pixelX;

                        if (_display[pixelIndex])
                            _registers[0xF] = 1;

                        _display[pixelIndex] ^= true;
                    }
                }
            }
            break;
        }

        default:
            std::cerr << "[Warning] Unhandled opcode: 0x" << std::hex << opcode << std::dec << "\n";
            break;
    }

    // === UPDATE TIMERS ===
    _timer->tick();
}

// === Getters / Setters  ===

[[nodiscard]] const std::array<bool, chip8::config::DISPLAY_X * chip8::config::DISPLAY_Y>&
chip8::Chip8::getDisplay() const
{
    return _display;
}

void
chip8::Chip8::setDisplayAt(std::size_t index, bool value)
{
    if (index < _display.size())
    {
        _display[index] = value;
    }
}

[[nodiscard]] const std::array<uint8_t, chip8::config::MEMORY_SIZE>&
chip8::Chip8::getMemory() const
{
    return _memory;
}

void
chip8::Chip8::setMemoryAt(std::size_t index, uint8_t value)
{
    if (index < _memory.size())
    {
        _memory[index] = value;
    }
}

[[nodiscard]] const std::array<uint8_t, chip8::config::REGISTER_SIZE>&
chip8::Chip8::getRegisters() const
{
    return _registers;
}

[[nodiscard]] uint16_t
chip8::Chip8::getRegisterIndex() const
{
    return _index_register;
}

[[nodiscard]] uint16_t
chip8::Chip8::getRegisterProgramCounter() const
{
    return _program_counter;
}

void
chip8::Chip8::setRegisterAt(std::size_t index, uint8_t value)
{
    if (index < _registers.size())
    {
        _registers[index] = value;
    }
}

void
chip8::Chip8::setRegisterIndex(uint16_t value)
{
    _index_register = value;
}

void
chip8::Chip8::setRegisterProgramCounter(uint16_t value)
{
    _program_counter = value;
}

[[nodiscard]] const std::array<uint16_t, chip8::config::STACK_SIZE>&
chip8::Chip8::getStack() const
{
    return _stack;
}

void
chip8::Chip8::setStackAt(std::size_t index, uint16_t value)
{
    if (index < _stack.size())
    {
        _stack[index] = value;
    }
}

[[nodiscard]] const chip8::Timers&
chip8::Chip8::getTimer() const
{
    return *_timer;
}