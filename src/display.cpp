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
  // Initialize the application to default settings
  setDefault();

  // Initialize the configuration if Present
  setConfig();

  // Initialize the window
  std::string title = _APP_NAME " - " _APP_VERSION;
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, app_w, app_h, SDL_WINDOW_SHOWN);
  if(window == nullptr) {
    std::cerr << "[CHIP8] SDL_WINDOW_ERROR: " << SDL_GetError() << std::endl;
    return;
  }

  // Initialize our renderer
  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(render == nullptr) {
    std::cerr << "[CHIP8] SDL_RENDER_ERROR: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    return;
  }

  // Configure colours
  SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
  SDL_RenderClear(render);
  SDL_SetRenderDrawColor(render, pixel_r, pixel_g, pixel_b, pixel_a);

  SDL_RenderPresent(render);

  initialized = true;
}


void DISPLAY::draw(const std::array<Byte, 2048>& display) {
  if(!initialized)
    return;

  // Clear the display
  this->clear();

  // Draw pixel's to the screen
  for(unsigned int pos = 0; pos < 2048; pos++) {
    if(display[pos] == 1) {
      // Calculate the xy coordinates
      unsigned int x = pos % 64;
      unsigned int y = pos / 64;

      // Generate a rect to represent our pixel
      SDL_Rect rect;
      rect.w = pixel_w;
      rect.h = pixel_h;
      rect.y = y * rect.h;
      rect.x = x * rect.w;


      // Draw to the render and present to the window
      SDL_RenderFillRect(render, &rect);
      SDL_RenderDrawRect(render, &rect);
    }
  }

  // Present the updated screen and set our last display var
  SDL_RenderPresent(render);
}


void DISPLAY::clear() {
  if(!initialized)
    return;

  SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
  SDL_RenderClear(render);
  SDL_SetRenderDrawColor(render, pixel_r, pixel_g, pixel_b, pixel_a);
}


void DISPLAY::finalize() {
  if(!initialized)
    return;

  initialized = false;
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
}


// ------- Display private functions

void DISPLAY::setDefault() {
  // These are the default display configuration settings
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
  std::ifstream in_stream(_APP_CONF, std::ifstream::binary);

  if(in_stream.is_open()) {
    // Read in the configuration file
    in_stream >> config;
    in_stream.close();

    // Update the display variables where a valid field is present
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
