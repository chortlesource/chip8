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

typedef std::uint8_t Byte;
typedef std::uint16_t Word;


// ------- LOCAL INCLUDES ------- //

// Local includes
#include "json.hpp"
#include "display.hpp"
#include "system.hpp"

#endif // _CHIP8_HPP
