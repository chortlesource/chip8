/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - display.cpp

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


// ------- DISPLAY Class Implementation ------- //

// Display public functions

void DISPLAY::initialize() {
  // Do something
}


void DISPLAY::draw(cont std::array<Byte, 2048>& display) {
  // Do something
}


void DISPLAY::clear() {
  // Do something
}


void DISPLAY::finalize() {
  // Do something
}


// ------- Display private functions

void DISPLAY::setDefault() {
  app_w = 320;
  app_h = 640;
  pixel_h = 10;
  pixel_w = 10;
  pixel_r = 255;
  pixel_g = 255;
  pixel_b = 255;
  pixel_a = 255;
}


void DISPLAY::setConfig() {
  Json::Value config;
  std::ifstream in_stream(_APP_CONFIG, std::ifstream::binary);
  if(in_stream.is_open()) {
    // Read in the relevant file
    in_stream >> config;
    in_stream.close();

    if(!config["APP_W"].empty())
      app_w = config["APP_W"].asUInt();

    if(!config["APP_H"].empty())
      app_h = config["APP_H"].asUInt();

    if(!config["PIXEL_H"].empty())
      pixel_h = config["PIXEL_H"].asUInt();

    if(!config["PIXEL_W"].empty())
      pixel_w = config["PIXEL_W"].asUInt();

    if(!config["PIXEL_R"].empty())
      pixel_r = config["PIXEL_R"].asUInt();

    if(!config["PIXEL_G"].empty())
      pixel_g = config["PIXEL_G"].asUInt();

    if(!config["PIXEL_B"].empty())
      pixel_b = config["PIXEL_B"].asUInt();

    if(!config["PIXEL_A"].empty())
      pixel_a = config["PIXEL_A"].asUInt();
  }
}
