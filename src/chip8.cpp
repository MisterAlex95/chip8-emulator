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
    std::fill(std::begin(memory), std::end(memory), 0);

    // Initialize registers
    std::fill(std::begin(V), std::end(V), 0);
    I = 0;
    pc = ROM_START_ADDRESS; // Program starts at ROM_START_ADDRESS

    // Initialize stack
    std::fill(std::begin(stack), std::end(stack), 0);
    sp = 0;

    // Initialize timers
    delay_timer = 0;
    sound_timer = 0;

    // Initialize keypad
    std::fill(std::begin(keys), std::end(keys), 0);

    // Initialize display
    display.fill(false);

    loadFontset();
}

void Chip8::loadFontset()
{
    // Load the fontset into memory
    for (size_t i = 0; i < CHIP8_FONTSET_SIZE; ++i)
    {
        memory[FONTSET_START_ADDRESS + i] = CHIP8_FONTSET[i];
    }
}

bool Chip8::loadROM(const char *filename)
{
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

    if (ROM_START_ADDRESS + size > sizeof(memory))
    {
        std::cerr << "ROM trop grande pour la mémoire\n";
        return false;
    }

    if (!ROM.read(reinterpret_cast<char *>(&memory[ROM_START_ADDRESS]), size))
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
    uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t kk = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;

    std::cout << std::hex << "Opcode [PC=" << pc << "]: 0x" << opcode << std::endl;

    // Avancer le PC *par défaut*, sauf si l'instruction saute ailleurs
    pc += 2;

    // === 2. DECODE + EXECUTE ===
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (opcode & 0x00FF)
        {
        case 0x00E0: // CLS : Clear screen
            display.fill(false);
            break;

        case 0x00EE: // RET : Return from subroutine
            if (sp == 0)
            {
                std::cerr << "Erreur : retour sans sous-routine\n";
                break;
            }
            --sp;
            pc = stack[sp];
            break;

        default:
            std::cerr << "Opcode inconnu 0x" << std::hex << opcode << "\n";
            break;
        }
        break;

    case 0x1000: // JP addr : Jump to address NNN
    {
        uint16_t address = opcode & 0x0FFF;
        pc = address;
        break;
    }

    default:
        std::cerr << "Opcode non géré: 0x" << std::hex << opcode << "\n";
        break;
    }

    // === 3. UPDATE TIMERS ===
    if (delay_timer > 0)
        --delay_timer;
    if (sound_timer > 0)
        --sound_timer;
}
