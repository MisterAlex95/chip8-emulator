#include "Memory.hh"
#include <iostream>

chip8::Memory::Memory()
{
    _memory.fill(0);
}

[[nodiscard]] int
chip8::Memory::getSize() const
{
    return _memory.size();
}

[[nodiscard]] uint8_t
chip8::Memory::getMemoryAt(std::size_t index) const
{
    #ifdef DEV_MODE
        std::cout << "Get PC: " << std::hex << index << std::endl;
    #endif

    if (index < _memory.size())
    {
        return _memory[index];
    }
    throw std::out_of_range("Memory access out of bounds");
}

void
chip8::Memory::setMemoryAt(std::size_t index, uint8_t value)
{
    #ifdef DEV_MODE
        std::cout << "Set PC: " << std::hex << index << std::endl;
    #endif
    if (index < _memory.size())
    {
        _memory[index] = value;
    }
}

[[nodiscard]] uint8_t*
chip8::Memory::data()
{
    return _memory.data();
}
[[nodiscard]] const uint8_t*
chip8::Memory::data() const
{
    return _memory.data();
}
