/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - system.hpp

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

#ifndef _CHIP8_SYSTEM_HPP
#define _CHIP8_SYSTEM_HPP

// ------- SYSTEM Class ------- //

/*
A container class for the Chip8 Program that parses
 command line input and executes the desired result.
*/

class SYSTEM {
public:
  // System enumeration
  enum class STATE { EXEC, PAUSE, HALT, ERR };

  // System public functions
  void initialize(const int argc, const char *argv[]);
  void run();
  void finalize();

private:
  // System Variables
  STATE state;
  bool config_enabled;
  bool debug_enabled;
  SDL_Event event;

  std::string file_path;
  std::string debug_path;
  float delay;

  // System Components
  DISPLAY display;
  CPU cpu;

  // System private functions
  bool fexist(const std::string& path);
  void parse(const int argc, const char *argv[]);
  void handleEvent();

};

#endif // _CHIP8_SYSTEM_HPP
