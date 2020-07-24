/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - memory.cpp

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

// ------- CHIP8_MEMORY Implementation ------- //

void CHIP8_MEMORY::open(const std::string& path, const Word& offset) {
  // Open a file stream
  std::ifstream input(path, std::ios::binary);
  if(input.is_open()){
    // Ascertain the size of the file
    input.seekg(0, input.end);
    auto fsize = input.tellg();
    input.seekg(0, input.beg);

    // Read in the data to a buffer
    char *buffer = new char[fsize];
    input.read(buffer, fsize);

    // Load the data from the buffer into memory
    for(Word i = 0; i < fsize; i++)
      MEMORY[offset + i] = static_cast<Byte>(buffer[i]);

    // Free the buffer
    delete [] buffer;
    std::cout << "[CHIP8] ROM File Loaded" << std::endl;
    return;
  }

  std::cerr << "[CHIP8] File not loaded." << std::endl;
}


void CHIP8_MEMORY::reset() {
  // Reset memory by filling with 0's
  MEMORY.fill(0);

  // Load fonts to memory
  for(unsigned int i = 0; i < 80; i++)
    MEMORY[i] = c8_fontset[i];
}


void CHIP8_MEMORY::write(const Word& addr, const Byte& value) {
  // Write the value to addr in memory
  MEMORY[addr] = value;
}


const Byte& CHIP8_MEMORY::read(const Word& addr) {
  // Return the addr value in memory
  return MEMORY[addr];
}
