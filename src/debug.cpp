/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - debug.cpp

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

#include "chip8.hpp"


// ------- DEBUG class implementation ------- //

// ------- Debug public functions

void DEBUG::start() {
  if(!enabled)
    return;

  // Open the log file and print the debug header
  output.open(log_path, std::ofstream::out | std::ofstream::app);

  for(int i = 0; i < 50; i++) output << "#";
  output << " DEBUGGING ";
  for(int i = 0; i < 51; i++) output << "#";   // Inequality makes me unhappy
  output << std::endl;
}


void DEBUG::stop() {
  // Print out our footer and close the log file
  for(int i = 0; i < 112; i++)
    output << "#";
  output << std::endl << std::endl;
  output.close();
}


void DEBUG::log_cpu_state(const Word& opcode, const std::array<Byte, 16>& registers, const Word& i, const Word& pc, const Byte& sp) {
  if(!enabled)
    return;

  if(output.is_open()) {
    // First print the opcode
    output << "| " << std::hex << std::setfill('0') << std::setw(4) << unsigned(opcode);

    // Print out all the register values
    for(unsigned int n = 0; n < registers.size(); n++)
      output << " |" << n << ":0x" << std::hex << std::setw(2) << unsigned(registers[n]);

    // Print out the i reg, pc and sp and flush the buffer
    output << " |I:0x" << std::hex << std::setw(4) << unsigned(i) <<
    " |PC:0x" << std::hex << std::setw(4) << unsigned(pc) <<
    " |SP:" << std::hex << std::setw(4) << unsigned(sp) << " |"<< std::endl;
  }
}


void DEBUG::log_mem_read(const Word& addr, const Byte& value) {
  if(!enabled)
    return;

  if(output.is_open()) {
    // Print output from the memory read instruction
    output << "| MEM-READ: 0x" << std::hex << std::setw(4) << unsigned(addr) <<
    " | FOUND: 0x" << std::hex << std::setw(2) << unsigned(value) << std::endl;
  }
}


void DEBUG::log_mem_write(const Word& addr, const Byte& value) {
  if(!enabled)
    return;

  if(output.is_open()) {
    // Print output from the memory write instruction
    output << "| MEM-WRITE: 0x" << std::hex << std::setw(4) << unsigned(addr) <<
    " | WROTE: 0x" << std::hex << std::setw(2) << unsigned(value) << std::endl;
  }
}
