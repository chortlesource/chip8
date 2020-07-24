/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - memory.hpp

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

#ifndef _CHIP8_MEMORY_HPP
#define _CHIP8_MEMORY_HPP


// ------- Memory Constants ------- //

static const Word MEM_SIZE = 0xFFF;


// ------- CHIP8_MEMORY Class ------- //

/*
A class to handle memory operations including ROM loading
*/

class CHIP8_MEMORY {
private:
  // CPU Memory
  std::array<Byte, MEM_SIZE> MEMORY;

public:
  void Open(const std::string& path, const Word& offset);
  void Reset();

  void Write(const Word& addr, const Byte& value);
  const Byte& Read(const Word& addr);

};


#endif // _CHIP8_MEMORY_HPP
