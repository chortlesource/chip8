/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - system.cpp

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


//------- Opcode Function Implementation ------- //

void CPU::opcode_none() {
  // Function to catch missing
  halt = true;
  std::cerr << "[CHIP8] Unexpected Opcode: " << std::to_string(opcode) << std::endl;
}


void CPU::opcode_nop() {
  // 0000 - No operation
  pc += 2;
}


void CPU::opcode_sys() {
  // 0NNN - Jump to NNN
  pc = memory_read(opcode);
}


void CPU::opcode_cls() {
  // 00E0 - Clear display
  display.fill(0);
  window->draw(display);
  pc += 2;
}


void CPU::opcode_ret() {
  // 00EE - Return from subroutine
  pc = stack[--sp];
  pc += 2;
}


void CPU::opcode_jmp() {
  // 1NNN - Jump to NNN
  pc = opcode & 0x0FFF;
}


void CPU::opcode_cal() {
  // 2NNN - Call subroutine at NNN
  stack[sp++] = pc;
  pc = opcode & 0x0FFF;
}


void CPU::opcode_si() {
  // 3XNN - Skip next instr if X == NN
  Byte x = (opcode & 0x0F00) >> 8;
  Byte nn = opcode & 0x00FF;

  if(registers[x] == nn)
    pc += 4;
  else
    pc += 2;
}


void CPU::opcode_snen() {
  // 4XNN - Skip next instr if reg X != NN
  Byte x = (opcode & 0x0F00) >> 8;
  Byte nn = opcode & 0x00FF;

  if(registers[x] != nn)
    pc += 4;
  else
    pc += 2;
}


void CPU::opcode_se() {
  // 5XY0 - Skip next instr if reg X = reg Y
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  if(registers[x] == registers[y])
    pc += 4;
  else
    pc += 2;
}


void CPU::opcode_ldn() {
  // 6XNN - Load NN into reg X
  Byte x = (opcode & 0x0F00) >> 8;
  registers[x] = opcode & 0x00FF;
  pc += 2;
}


void CPU::opcode_adn() {
  // 7XNN - Set reg x += NN
  Byte x = (opcode & 0x0F00) >> 8;
  registers[x] += (opcode & 0x00FF);
  pc += 2;
}


void CPU::opcode_ldx() {
  // 8XY0 - Set reg x = reg y
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  registers[x] = registers[y];
  pc += 2;
}


void CPU::opcode_orx() {
  // 8XY1 - Set reg x |= reg y
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  registers[x] |= registers[y];
  pc += 2;
}


void CPU::opcode_anx() {
  // 8XY2 - Set reg x &= reg y
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  registers[x] &= registers[y];
  pc += 2;
}


void CPU::opcode_xor() {
  // 8XY3 - Set reg x ^= reg y
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  registers[x] ^= registers[y];
  pc += 2;
}


void CPU::opcode_adc() {
  // 8XY4 - Set reg x += reg y [REG F]
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  // Add the registers
  Word value = registers[x] + registers[y];
  registers[x] = value & 0xFFFF;

  // Set the carry flag
  registers[0xF] = (value & 0xF0000) >> 16;
  pc += 2;
}


void CPU::opcode_sub() {
  // 8XY5 - Set reg x -= reg y [REG F]
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  // Set the carry flag
  if(registers[x] > registers[y])
    registers[0xF] = 1;
  else
    registers[0xF] = 0;

  // Subtract the registers
  Word value = registers[x] - registers[y];
  registers[x] = value & 0xFFFF;
  pc += 2;
}


void CPU::opcode_srh() {
  // 8XY6 - Set reg x >>= 1 [REG F]
  Byte x = (opcode & 0x0F00) >> 8;

  // Set the carry flag
  registers[0xF] = registers[x] & 0x1;

  registers[x] >>= 1;
  pc += 2;
}


void CPU::opcode_subn() {
  // 8XY7 - Set reg x = x - y [REG F]
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  // Set the carry flag
  if(registers[y] > registers[x])
    registers[0xF] = 1;
  else
    registers[0xF] = 0;

  // Subtract the registers
  Word value = registers[y] - registers[x];
  registers[x] = value & 0xFFFF;
  pc += 2;
}


void CPU::opcode_shl() {
  // 8XYE - Set reg x <<= 1 [REG F]
  Byte x = (opcode & 0x0F00) >> 8;

  // Set the MSB flag
  registers[0xF] = (registers[x] & 0x80) >> 7;

  registers[x] <<= 1;
  pc += 2;
}


void CPU::opcode_sney() {
  // 9XY0 - Skip next instr if reg x != reg Y
  Byte x = (opcode & 0x0F00) >> 8;
  Byte y = (opcode & 0x00F0) >> 4;

  if(registers[x] != registers[y])
    pc += 4;
  else
    pc += 2;
}


void CPU::opcode_ldi() {
  // ANNN - Set reg I = NNN
  i = opcode & 0xFFF;
  pc += 2;
}


void CPU::opcode_jpa() {
  // BNNN - Set PC = NNN + reg 0
  pc = (opcode & 0xFFF) + registers[0];
}


void CPU::opcode_rnd() {
  // CXNN - Set reg x = (RANDOM) & NN
  Byte x = (opcode & 0x0F00) >> 8;
  Byte nn = (opcode & 0x00FF);

  registers[x] = randomNumber(0, 0xFF) & nn;

  pc += 2;
}


void CPU::opcode_drw() {
  // DXYN - Draw function
  Byte x = registers[(opcode & 0x0F00) >> 8];
  Byte y = registers[(opcode & 0x00F0) >> 4];
  Byte h = opcode & 0x000F;
  Byte pixel = 0;

  // Set the VF register to 0
  registers[0xF] = 0;

  for(int ypos = 0; ypos < h; ypos++) {
    // Read the pixel to memory
    pixel = memory_read(ypos + i);
    for(int xpos = 0; xpos < 8; xpos++) {
      if((pixel & (0x80 >> xpos)) != 0) {
        // Check for collision
        if(display[(x + xpos + ((y + ypos) * 64))] == 1)
          registers[0xF] = 1;
        // Set the pixel
        display[(x + xpos + ((y + ypos) * 64))] ^= 1;
      }
    }
  }

  window->draw(display);
  pc += 2;
}


void CPU::opcode_skp() {
  // EX9E - Skip instr if key X == pressed
  Byte x = registers[(opcode & 0x0F00) >> 8];

  if(key[x] != 0) {
    key[x] = 0;
    pc += 2;
  }

  pc += 2;
}


void CPU::opcode_sknp() {
  // EXA1 - Skip instr if key x != pressed
  Byte x = registers[(opcode & 0x0F00) >> 8];

  if(key[x] == 0)
    pc += 2;

  pc += 2;
}


void CPU::opcode_lxd(){
  // FX07 - reg x = delay timer
  Byte x = (opcode & 0x0F00) >> 8;

  registers[x] = delay_timer;
  pc += 2;
}


void CPU::opcode_ldk() {
  // FX0A - Wait for key and store in reg x
  SDL_Event event;
  SDL_WaitEvent(&event);
  
  switch(event.type) {
    case SDL_QUIT:
      halt = true;
      return;
    case SDL_KEYDOWN:
      for(unsigned int n = 0; n < 16; n++) {
        if(event.key.keysym.sym == chip8_key[n]) {
          registers[(opcode & 0x0F00) >> 8] = n;
          key[n] = 1;
          pc += 2;
          return;
        }
      }
      break;
    default:
      break;
  }

  pc += 2;
}


void CPU::opcode_ldt() {
  // FX15 - delay timer = reg x
  Byte x = (opcode & 0x0F00) >> 8;

  delay_timer = registers[x];
  pc += 2;
}


void CPU::opcode_lsx() {
  // FX18 - sound timer = reg x
  Byte x = (opcode & 0x0F00) >> 8;

  sound_timer = registers[x];
  pc += 2;
}


void CPU::opcode_adi() {
  // FX1E - Set reg i += reg x
  Byte x = (opcode & 0x0F00) >> 8;

  i += registers[x];
  pc += 2;
}


void CPU::opcode_lds() {
  // FX29 - reg I = (SPRITE X)
  Byte x = (opcode & 0x0F00) >> 8;

  i = registers[x] * 5;
  pc += 2;
}


void CPU::opcode_ldb() {
  // FX33 - Store reg x in mem[reg i++]
  Byte x = (opcode & 0x0F00) >> 8;

  Byte value = registers[x];
  memory_write(i, value / 100);
  memory_write(i + 1, (value / 10) % 10);
  memory_write(i + 2, (value % 100) %10);
  pc += 2;
}


void CPU::opcode_ldm() {
  // FX55 - Store reg 0 -> reg x in mem[reg I]
  Byte x = (opcode & 0x0F00) >> 8;
  ++x;  // Increment to include x in the reg dump

  for(Byte n = 0; n < x; n++)
    memory_write(i + n, registers[n]);
  pc += 2;
}


void CPU::opcode_rdx() {
  // FX65 - Read reg 0 -> reg x from mem[reg I]
  Byte x = (opcode & 0x0F00) >> 8;
  ++x;  // Increment to include x in the reg pull

  for(Byte n = 0; n < x; n++)
    registers[n] = memory_read(i + n);
  pc += 2;
}
