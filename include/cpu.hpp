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
  // CPU public functions
  void initialize(DISPLAY *d);
  void update();
  void reset();

  void open(const std::string& path, const Word& offset);

  // CPU debug functions
  // void Debug(const std::string& path, const bool& enabled);
  // void debugStart() { dbug.start(); }
  // void debugStop() { dbug.stop(); }

  const bool& isHalt() { return halt; }
  void setHalt(const bool& h) { halt = h; }

  void setKey(const int& n);

private:
  // CPU variables
  bool initialized;
  bool halt;
  Word opcode;

  // CPU pointers
  OPFUNC opfunc;
  DISPLAY *window;

  // CPU utilities
  CHIP8_MEMORY memory;

  // CPU registers
  std::array<Byte, 16> registers;
  Word i;
  Word pc;
  Byte sp;
  std::array<Word, 16> stack;
  std::array<unsigned char, 2048> display;
  std::array<Byte, 16> key;

  // CPU timers
  Byte delay_timer;
  Byte sound_timer;

  // CPU opcode functions
  void opcode_none();   // Function to catch missing
  void opcode_nop();    // 0000 - No operation
  void opcode_sys();    // 0NNN - Jump to NNN
  void opcode_cls();    // 00E0 - Clear display
  void opcode_ret();    // 00EE - Return from subroutine
  void opcode_jmp();    // 1NNN - Jump to NNN
  void opcode_cal();    // 2NNN - Call subroutine at NNN
  void opcode_si();     // 3XNN - Skip next instr if reg X == NN
  void opcode_snen();   // 4XNN - Skip next instr if reg X != NN
  void opcode_se();     // 5XY0 - Skip next instr if reg X = reg Y
  void opcode_ldn();    // 6XNN - Load NN into reg X

  void opcode_adn();    // 7XNN - Set reg x += NN
  void opcode_ldx();    // 8XY0 - Set reg x = reg y
  void opcode_orx();    // 8XY1 - Set reg x |= reg y
  void opcode_anx();    // 8XY2 - Set reg x &= reg y
  void opcode_xor();    // 8XY3 - Set reg x ^= reg y
  void opcode_adc();    // 8XY4 - Set reg x += reg y [REG F]
  void opcode_sub();    // 8XY5 - Set reg x -= reg y [REG F]
  void opcode_srh();    // 8XY6 - Set reg x >>= 1 [REG F]
  void opcode_subn();   // 8XY7 - Set reg x = x - y [REG F]
  void opcode_shl();    // 8XYE - Set reg x <<= 1 [REG F]

  void opcode_sney();   // 9XY0 - Skip next instr if reg x != reg Y
  void opcode_ldi();    // ANNN - Set reg I = NNN
  void opcode_jpa();    // BNNN - Set PC = NNN + reg 0
  void opcode_rnd();    // CXNN - Set reg x = (RANDOM) & NN
  void opcode_drw();    // DXYN - Draw function
  void opcode_skp();    // EX9E - Skip instr if key X == pressed
  void opcode_sknp();   // EXA1 - Skip instr if key x != pressed
  void opcode_lxd();    // FX07 - reg x = delay timer
  void opcode_ldk();    // FX0A - Wait for key and store in reg x
  void opcode_ldt();    // FX15 - delay timer = reg x
  void opcode_lsx();    // FX18 - sound timer = reg x
  void opcode_adi();    // FX1E - Set reg i += reg x
  void opcode_lds();    // FX29 - reg I = (SPRITE X)
  void opcode_ldb();    // FX33 - Store reg x in mem[reg i++]
  void opcode_ldm();    // FX55 - Store reg 0 -> reg x in mem[reg I]
  void opcode_rdx();    // FX65 - Read reg 0 -> reg x from mem[reg I]

  // CPU privte functions
  void fetch();
  void decode();
  void execute();

  const Byte& memory_read(const Word& addr);
  void memory_write(const Word& addr, const Byte& value);
  Byte randomNumber(const Byte& l, const Byte& h);
};


#endif // _CHIP8_CPU_HPP
