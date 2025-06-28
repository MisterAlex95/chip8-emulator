#include <gtest/gtest.h>
#include "chip8.hh"

TEST(Chip8Test, InitializeResetsState)
{
    Chip8 chip;
    chip.initialize();

    // Vérifie que la mémoire, les registres, le PC, la pile, les timers et l'affichage sont bien réinitialisés
    for (int i = 0; i < MEMORY_SIZE; ++i)
        EXPECT_EQ(chip.getMemory()[i], 0);

    for (int i = 0; i < REGISTER_SIZE; ++i)
        EXPECT_EQ(chip.getRegisters()[i], 0);

    EXPECT_EQ(chip.getRegisterIndex(), 0);
    EXPECT_EQ(chip.getRegisterProgramCounter(), ROM_START_ADDRESS);

    for (int i = 0; i < STACK_SIZE; ++i)
        EXPECT_EQ(chip.getStack()[i], 0);

    EXPECT_EQ(chip.getRegisterProgramCounter(), ROM_START_ADDRESS);
    EXPECT_EQ(chip.getDelayTimer(), 0);
    EXPECT_EQ(chip.getSoundTimer(), 0);

    auto display = chip.getDisplay();
    for (auto pixel : display)
        EXPECT_FALSE(pixel);
}

TEST(Chip8Test, LoadROMFailsWithNullFilename)
{
    Chip8 chip;
    chip.initialize();
    EXPECT_FALSE(chip.loadROM(nullptr));
}

TEST(Chip8Test, CycleCLSOpcodeClearsDisplay)
{
    Chip8 chip;
    chip.initialize();

    // Allume quelques pixels
    auto display = chip.getDisplay();
    for (int i = 0; i < display.size(); ++i)
        chip.setDisplayAt(i, true);

    // Place l'opcode CLS (0x00E0) à l'adresse PC
    chip.setMemoryAt(chip.getRegisterProgramCounter(), 0x00);
    chip.setMemoryAt(chip.getRegisterProgramCounter() + 1, 0xE0);

    chip.cycle();

    auto cleared = chip.getDisplay();
    for (auto pixel : cleared)
        EXPECT_FALSE(pixel);
}