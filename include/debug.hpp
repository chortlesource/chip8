/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - debug.hpp

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

#ifndef _CHIP8_DEBUG_HPP
#define _CHIP8_DEBUG_HPP


// ------- DEBUG Class ------- //

/*
A class that aids with debugging the CHIP8 Emulator by creating
a log file with all operations
*/

class DEBUG {
public:
  // Debug public functions
  void start();
  void stop();

  void log_cpu_state(const Word& opcode, const std::array<Byte, 16>& registers, const Word& i, const Word& pc, const Byte& sp);
  void log_mem_read(const Word& addr, const Byte& value);
  void log_mem_write(const Word& addr, const Byte& value);

  void initialize(const std::string& path) { log_path = path; }
  void setEnabled(const bool& e) { enabled = e;}

private:
  // Debug variables
  bool enabled;

  std::string log_path;
  std::ofstream output;

};


#endif // _CH8P_DEBUG_HPP
