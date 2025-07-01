#ifndef MEMORY_HH
#define MEMORY_HH

#include <array>

#include "Constants.hh"

namespace chip8
{
    class Memory
    {
       public:
        Memory();

        [[nodiscard]] int            getSize() const;
        [[nodiscard]] uint8_t        getMemoryAt(std::size_t index) const;
        void                         setMemoryAt(std::size_t index, uint8_t value);

        [[nodiscard]] uint8_t*       data();
        [[nodiscard]] const uint8_t* data() const;

       private:
        std::array<uint8_t, chip8::config::MEMORY_SIZE> _memory;  // 4K memory
    };

}  // namespace chip8

#endif  // MEMORY_HH
