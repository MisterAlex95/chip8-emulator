#ifndef MEMORY_HH
#define MEMORY_HH

#include <array>

#include "Constants.hh"
#include "Types.hh"

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
        MemoryArray _memory;  // 4K memory
    };

}  // namespace chip8

#endif  // MEMORY_HH
