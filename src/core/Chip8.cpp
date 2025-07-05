#include <fstream>
#include <iostream>

#include "Chip8.hh"
#include "Constants.hh"
#include "Fontset.hh"
#include "Timers.hh"

chip8::Chip8::Chip8(chip8::IKeyboard* keyboard)
    : _keyboard(keyboard),
      _memory(std::make_unique<Memory>()),
      _display(std::make_unique<Display>()),
      _timer(std::make_unique<Timers>())
{
    _cpu = std::make_unique<CPU>(_memory.get(), _display.get(), _timer.get(), keyboard);
    loadFontSet();
}

void
chip8::Chip8::loadFontSet()
{
    for (size_t i = 0; i < chip8::CHIP8_FONTSET_SIZE; ++i)
    {
        _memory->setMemoryAt(chip8::config::FONTSET_START_ADDRESS + i, chip8::CHIP8_FONTSET[i]);
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

    if (chip8::config::ROM_START_ADDRESS + size > _memory->getSize())
    {
        std::cerr << "[Error] ROM size exceeds memory capacity\n";
        return false;
    }

    if (!romFile.read(reinterpret_cast<char*>(_memory->data() + chip8::config::ROM_START_ADDRESS),
                      size))
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
    this->_cpu->cycle();
}

[[nodiscard]] chip8::Timers*
chip8::Chip8::getTimer() const
{
    return _timer.get();
}

[[nodiscard]] chip8::Display*
chip8::Chip8::getDisplay() const
{
    return _display.get();
}

[[nodiscard]] chip8::Memory*
chip8::Chip8::getMemory() const
{
    return _memory.get();
}

[[nodiscard]] chip8::CPU*
chip8::Chip8::getCPU() const
{
    return _cpu.get();
}

[[nodiscard]] chip8::IKeyboard*
chip8::Chip8::getKeyboard() const
{
    return _keyboard.get();
}
