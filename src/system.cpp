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


// ------- SYSTEM Class Implementation ------- //

// ------- System public functions

void SYSTEM::initialize(const int argc, const char *argv[]) {
  state = STATE::HALT;    // by default end the program

  // Ascertain if a configuration file is present
  config_enabled = fexist("assets/config.json");
  debug_enabled = false;

  parse(argc, argv);
}


void SYSTEM::run() {
  // Do something
}


void SYSTEM::finalize() {
  // Do something
}


// ------- System private functions

namespace fs = std::experimental::filesystem;

bool SYSTEM::fexist(const std::string& path) {
  // Identify if file exists and return true if exists
  return (fs::exists(fs::path(path)) && fs::is_regular_file(fs::path(path)));
}


void SYSTEM::parse(const int argc, const char *argv[]) {
  // Catch possible misuse
  if(argc < 2) {
    std::cerr << "[CHIP8] Usage:\t" << argv[0] << " <ROM_PATH>" << std::endl;
    std::cerr << "\t\t" << argv[0] << " <ROM_PATH> -D <DEBUG_PATH>" << std::endl;
    std::cerr << "\t\t" << argv[0] << " -h" << std::endl;
    return;
  }

  // Add our arguments to a vector of strings
  std::vector<std::string> args;

  for(int i = 0; i < argc; i++)
    args.push_back(argv[i]);


  switch(argc) {
    case 2:
      {
        // Handle calls to help
        if(!args[1].compare("-h") || !args[1].compare("-H")) {
          std::cout << "[CHIP8] " << _APP_VERSION << " by " << _APP_AUTHOR << std::endl;
          return;
        }

        // Ensure we are using a rom that exists
        if(fexist(args[1])) {
          // Configure our system to run the ROM only
          file_path = args[1];
          debug_enabled = false;
          state = STATE::EXEC;

          std::cout << "[CHIP8] Found ROM: " << file_path << std::endl;
        } else {
          // Catch missing files
          std::cerr << "[CHIP8] Unable to find ROM: " << args[1] << std::endl;
        }
      }
      break;
    case 4:
      {
        if(!args[2].compare("-D") || !args[2].compare("-d")) {
          // Ensure we are not reusing logfiles
          if(fexist(args[3])) {
            std::cerr << "[CHIP8] File already exists please specify an alternative." << std::endl;
            break;
          }
          // Ensure we are using a rom that exists
          if(fexist(args[1])) {
            // Configure our system to run the ROM and debug
            file_path = args[1];
            debug_path = args[2];
            debug_enabled = true;
            state = STATE::EXEC;

            std::cout << "[CHIP8] Found ROM: " << file_path << std::endl;
            std::cout << "[CHIP8] Debugging enabled" << std::endl;
            break;
          } else {
            // Catch a missing rom
            std::cerr << "[CHIP8] Unable to find ROM: " << args[1] << std::endl;
            break;
          }
        }
      }
    default:
      {
        // Catch unknown commands
        std::cerr << "[CHIP8] Usage:\t" << argv[0] << " <ROM_PATH>" << std::endl;
        std::cerr << "\t\t" << argv[0] << " <ROM_PATH> -D <DEBUG_PATH>" << std::endl;
        std::cerr << "\t\t" << argv[0] << " -h" << std::endl;
        return;
      }
  }
}


void SYSTEM::handleEvent() {
  // Do something
}
