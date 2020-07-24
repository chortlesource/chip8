/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - cpu.cpp

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


// ------- CPU public functions

void CPU::initialize(DISPLAY *d) {
  window = d;
  reset();  //
}


void CPU::update() {
  fetch();                      // Fetch
  decode();                     // Decode

  // Log CPU Status
  // dbug.cpulog(opcode, registers, i, pc, sp);

  execute();                    // Execute
  --delay_timer;
  --sound_timer;
}


void CPU::reset() {
  // Reset Memory
  memory.reset();

  // Reset CPU
  registers.fill(0);
  i = 0;
  pc = 0x200;
  sp = 0;
  stack.fill(0);
  display.fill(0);
  key.fill(0);

  delay_timer = 0;
  sound_timer = 0;

  opcode = 0;

  halt = false;
}


void CPU::open(const std::string& path, const Word& offset) {
  memory.open(path, offset);
  initialized = true;
}


void CPU::setKey(const int& n) {
  key.fill(0);
  key[n] = 1;
}


// ------- CPU private functions

void CPU::fetch() {
  // Fetch the next instruction
  Byte msb = memory_read(pc);
  Byte lsb = memory_read(pc + 1);

  // Assemble the opcode
  opcode = (msb << 8) | lsb;
}


void CPU::decode() {
  // Opcode switch to determine which operation
  switch(opcode & 0xF000) {
    case 0x0000:
      switch(opcode & 0xFF) {
        case 0x00:
          opfunc = &CPU::opcode_nop;
          break;
        case 0xE0:
          opfunc = &CPU::opcode_cls;
          break;
        case 0xEE:
          opfunc = &CPU::opcode_ret;
          break;
        default:
          opfunc = &CPU::opcode_sys;
          break;
      };
      break;
    case 0x1000:
      opfunc = &CPU::opcode_jmp;
      break;
    case 0x2000:
      opfunc = &CPU::opcode_cal;
      break;
    case 0x3000:
      opfunc = &CPU::opcode_si;
      break;
    case 0x4000:
      opfunc = &CPU::opcode_snen;
      break;
    case 0x5000:
      {
        if(opcode & 0xF)
          opfunc = &CPU::opcode_none;
        else
          opfunc = &CPU::opcode_se;
      }
      break;
    case 0x6000:
      opfunc = &CPU::opcode_ldn;
      break;
    case 0x7000:
      opfunc = &CPU::opcode_adn;
      break;
    case 0x8000:
      switch(opcode & 0xF) {
        case 0x0:
          opfunc = &CPU::opcode_ldx;
          break;
        case 0x1:
          opfunc = &CPU::opcode_orx;
          break;
        case 0x2:
          opfunc = &CPU::opcode_anx;
          break;
        case 0x3:
          opfunc = &CPU::opcode_xor;
          break;
        case 0x4:
          opfunc = &CPU::opcode_adc;
          break;
        case 0x5:
          opfunc = &CPU::opcode_sub;
          break;
        case 0x6:
          opfunc = &CPU::opcode_srh;
          break;
        case 0x7:
          opfunc = &CPU::opcode_subn;
          break;
        case 0xE:
          opfunc = &CPU::opcode_shl;
          break;
        default:
          opfunc = &CPU::opcode_none;
          break;
      };
      break;
    case 0x9000:
      {
        if(opcode & 0xF)
          opfunc = &CPU::opcode_none;
        else
          opfunc = &CPU::opcode_sney;
      }
      break;
    case 0xA000:
      opfunc = &CPU::opcode_ldi;
      break;
    case 0xB000:
      opfunc = &CPU::opcode_jpa;
      break;
    case 0xC000:
      opfunc = &CPU::opcode_rnd;
      break;
    case 0xD000:
      opfunc = &CPU::opcode_drw;
      break;
    case 0xE000:
      switch(opcode & 0xFF) {
        case 0x9E:
          opfunc = &CPU::opcode_skp;
          break;
        case 0xA1:
          opfunc = &CPU::opcode_sknp;
          break;
        default:
          opfunc = &CPU::opcode_none;
          break;
      };
      break;
    case 0xF000:
      switch(opcode & 0xFF) {
        case 0x07:
          opfunc = &CPU::opcode_lxd;
          break;
        case 0x0A:
          opfunc = &CPU::opcode_ldk;
          break;
        case 0x15:
          opfunc = &CPU::opcode_ldt;
          break;
        case 0x18:
          opfunc = &CPU::opcode_lsx;
          break;
        case 0x1E:
          opfunc = &CPU::opcode_adi;
          break;
        case 0x29:
          opfunc = &CPU::opcode_lds;
          break;
        case 0x33:
          opfunc = &CPU::opcode_ldb;
          break;
        case 0x55:
          opfunc = &CPU::opcode_ldm;
          break;
        case 0x65:
          opfunc = &CPU::opcode_rdx;
          break;
        default:
          opfunc = &CPU::opcode_none;
          break;
      };
      break;
    default:
      opfunc = &CPU::opcode_none;
      break;
    }
}


void CPU::execute() {
  // Execute the relevant opcode function
  (this->*opfunc)();
}


const Byte& CPU::memory_read(const Word& addr) {
  // Wrapper to log memory read data
  //dbug.memlog_r(addr, memory.Read(addr));
  return memory.read(addr);
}


void CPU::memory_write(const Word& addr, const Byte& value) {
  // Wrapper to log memory write data
  //dbug.memlog_w(addr, value);
  memory.write(addr, value);
}


Byte CPU::randomNumber(const Byte& l, const Byte& h) {
  std::random_device device;  // obtain random number from device
  std::mt19937 gen(device()); // seed the generator
  std::uniform_int_distribution<> distr(l, h); // define the range

  return distr(gen);
}
