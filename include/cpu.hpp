/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - cpu.hpp

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

#ifndef _CHIP8_CPU_HPP
#define _CHIP8_CPU_HPP


// ------- CPU Class ------- //

/*
The CHIP8 CPU implemented in a class. This requires call back functions
to be passed to utilise relevant functions such as draw()
*/

class CPU {
public:


private:
  // CPU Variables
  bool pause;
  bool halt;

  Word opcode;
  OPFUNC opfunc;

    
};


#endif // _CHIP8_CPU_HPP
