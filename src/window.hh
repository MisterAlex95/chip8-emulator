#pragma once

#include "core/Chip8.hh"

#include "interfaces/IDisplay.hh"
#include "interfaces/IInput.hh"
#include "interfaces/ITimer.hh"

void
mainLoop(chip8::Chip8* chip8, IInput& input, IDisplay& display, ITimer& timer);