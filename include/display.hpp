/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

chip8 - display.hpp

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

#ifndef _CHIP8_DISPLAY_HPP
#define _CHIP8_DISPLAY_HPP


// ------- DISPLAY Class ------- //

/*
A container class for the SDL Display which handles
window updates and configuration
*/

class DISPLAY {
public:
  // Display public functions
  void initialize();
  void draw(const std::array<Byte, 2048>& display);
  void clear();
  void finalize();

  const float& getDelay() { return app_delay; }

private:
  // Display variables
  bool initialized;
  SDL_Window *window;
  SDL_Renderer *render;

  float app_delay;
  unsigned int app_w;
  unsigned int app_h;
  unsigned int pixel_h;
  unsigned int pixel_w;
  unsigned int pixel_r;
  unsigned int pixel_g;
  unsigned int pixel_b;
  unsigned int pixel_a;

  // Display private functions
  void setDefault();
  void setConfig();
};

#endif // _CHIP8_DISPLAY_HPP
