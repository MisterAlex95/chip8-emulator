#include <array>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "chip8.hh"
#include "fontset.hh"

void Chip8::initialize()
{
    // Initialize memory
    _memory.fill(0);

    // Initialize registers
    _registers.fill(0);
    _index_register = 0;
    _program_counter = ROM_START_ADDRESS; // Program starts at ROM_START_ADDRESS

    // Initialize stack
    _stack.fill(0);
    _stack_pointer = 0;

    // Initialize timers
    _delay_timer = 0;
    _sound_timer = 0;

    // Initialize keypad
    std::fill(std::begin(_keys), std::end(_keys), 0);

    // Initialize display
    _display.fill(false);
}

void Chip8::loadFontset()
{
    // Load the fontset into memory
    for (size_t i = 0; i < CHIP8_FONTSET_SIZE; ++i)
    {
        _memory[FONTSET_START_ADDRESS + i] = CHIP8_FONTSET[i];
    }
}

bool Chip8::loadROM(const char *filename)
{
    if (!filename)
    {
        std::cout << "Filename is empty\n";
        return false;
    }

    // Read .ch8 file
    std::cout << "Chargement de la ROM : " << filename << "\n";
    std::ifstream ROM(filename, std::ifstream::binary);

    if (!ROM.is_open())
    {
        std::cerr << "Impossible d'ouvrir le fichier ROM\n";
        return false;
    }

    ROM.seekg(0, std::ios::end);
    std::streamsize size = ROM.tellg();
    std::cout << "ROM size: " << size << " bytes\n";
    ROM.seekg(0, std::ios::beg);

    if (size <= 0)
    {
        std::cerr << "ROM vide ou erreur de lecture\n";
        return false;
    }

    if (ROM_START_ADDRESS + size > sizeof(_memory))
    {
        std::cerr << "ROM trop grande pour la mémoire\n";
        return false;
    }

    if (!ROM.read(reinterpret_cast<char *>(&_memory[ROM_START_ADDRESS]), size))
    {
        std::cerr << "Erreur lors de la lecture de la ROM\n";
        return false;
    }
    std::cout << "ROM chargée avec succès.\n";

    return true;
}

void Chip8::cycle()
{
    // === 1. FETCH ===
    uint16_t opcode = (_memory[_program_counter] << 8) | _memory[_program_counter + 1];

    // std::cout << std::hex << "Opcode [PC=" << pc << "]: 0x" << opcode << std::endl;

    // Avancer le PC *par défaut*, sauf si l'instruction saute ailleurs
    _program_counter += 2;

    // === 2. DECODE + EXECUTE ===
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (opcode & 0x00FF)
        {
        case 0x00E0: // CLS : Clear screen
            _display.fill(false);
            break;

        case 0x00EE: // RET : Return from subroutine
            if (_stack_pointer == 0)
            {
                std::cerr << "Erreur : retour sans sous-routine\n";
                break;
            }
            --_stack_pointer;
            _program_counter = _stack[_stack_pointer];
            break;

        default:
            std::cerr << "Opcode inconnu 0x" << std::hex << opcode << "\n";
            break;
        }
        break;

    case 0x1000: // JP addr : Jump to address NNN
    {
        uint16_t address = opcode & 0x0FFF;
        _program_counter = address;
        break;
    }

    case 0xD000: // Dxyn
    {
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t y = (opcode & 0x00F0) >> 4;
        uint8_t height = opcode & 0x000F;

        _registers[0xF] = 0; // Reset collision flag

        for (int row = 0; row < height; ++row)
        {
            uint8_t spriteByte = _memory[_index_register + row];
            for (int col = 0; col < 8; ++col)
            {
                bool spritePixel = (spriteByte & (0x80 >> col)) != 0;
                if (spritePixel)
                {
                    // Calculer la position sur l’écran en tenant compte du wrapping
                    uint16_t pixelX = (_registers[x] + col) % 64;
                    uint16_t pixelY = (_registers[y] + row) % 32;
                    uint16_t pixelIndex = pixelY * 64 + pixelX;

                    // Collision si pixel à l’écran était allumé et sera éteint après XOR
                    if (_display[pixelIndex] == true)
                        _registers[0xF] = 1;

                    // XOR du pixel
                    _display[pixelIndex] ^= true;
                }
            }
        }
        break;
    }

    default:
        std::cerr << "Opcode non géré: 0x" << std::hex << opcode << "\n";
        break;
    }

    // === 3. UPDATE TIMERS ===
    if (_delay_timer > 0)
        --_delay_timer;
    if (_sound_timer > 0)
        --_sound_timer;
}

const std::array<bool, DISPLAY_Y * DISPLAY_X> Chip8::getDisplay()
{
    return this->_display;
}

void Chip8::setDisplayAt(uint8_t index, bool value)
{
    if (this->_display.size() <= index && index >= 0)
    {
        this->_display[index] = value;
    }
}

const std::array<uint8_t, MEMORY_SIZE> Chip8::getMemory()
{
    return this->_memory;
}

void Chip8::setMemoryAt(uint8_t index, uint8_t value)
{
    if (this->_memory.size() <= index && index >= 0)
    {
        this->_memory[index] = value;
    }
}

const std::array<uint8_t, REGISTER_SIZE> Chip8::getRegisters()
{
    return this->_registers;
}

const uint16_t Chip8::getRegisterIndex()
{
    return this->_index_register;
}

const uint16_t Chip8::getRegisterProgramCounter()
{
    return this->_program_counter;
}

void Chip8::setRegisterAt(uint8_t index, uint8_t value)
{
    if (this->_registers.size() <= index && index >= 0)
    {
        this->_registers[index] = value;
    }
}

void Chip8::setRegisterIndex(uint16_t value)
{
    this->_index_register = value;
}

void Chip8::setRegisterProgramCounter(uint16_t value)
{
    this->_program_counter = value;
}

const std::array<uint16_t, STACK_SIZE> Chip8::getStack()
{
    return this->_stack;
}

void Chip8::setStackAt(uint8_t index, uint16_t value)
{
    if (this->_stack.size() <= index && index >= 0)
    {
        this->_stack[index] = value;
    }
}

const uint8_t Chip8::getDelayTimer()
{
    return this->_delay_timer;
}

const uint8_t Chip8::getSoundTimer()
{
    return this->_sound_timer;
}

void Chip8::setDelayTimer(uint8_t value)
{
    this->_delay_timer = value;
}

void Chip8::setSoundTimer(uint8_t value)
{
    this->_sound_timer = value;
}
