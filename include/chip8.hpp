/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - chip8.hpp

Copyright (c) 2020 Christopher M. Short

This file is part of chip8.

chip8 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

chip8 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with chip8. If not, see <https://www.gnu.org/licenses/>.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CHIP8_HPP
#define _CHIP8_HPP

/*
This file contains the application macros, forwards,
types and libraries used by the application
*/

// ------- APP NOTES ------- //

#define _APP_NAME "chip8"
#define _APP_VERSION "0.0.1-BETA"
#define _APP_AUTHOR "C. M. Short"
#define _APP_SOURCE "http://www.github.com/chortlesoft/chip8"
#define _APP_CONF "assets/config.json"


// ------- LIBRARY INCLUDES ------- //

// Standard libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <cstdint>

#include <string>
#include <vector>
#include <array>
#include <random>
#include <experimental/filesystem>

// Dependencies
#include <SDL2/SDL.h>


// ------- FORWARDS ------- //

class SYSTEM;
class CPU;

typedef std::uint8_t Byte;
typedef std::uint16_t Word;
typedef void (CPU::*OPFUNC)();

static const unsigned char c8_fontset[80] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

static const SDL_Keycode chip8_key[16] =
{
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_4,
    SDLK_q,
    SDLK_w,
    SDLK_e,
    SDLK_r,
    SDLK_a,
    SDLK_s,
    SDLK_d,
    SDLK_f,
    SDLK_z,
    SDLK_x,
    SDLK_c,
    SDLK_v
};


// ------- LOCAL INCLUDES ------- //

// Local includes
#include "json.hpp"
#include "memory.hpp"
#include "display.hpp"
#include "cpu.hpp"
#include "system.hpp"

#endif // _CHIP8_HPP
