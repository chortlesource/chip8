# CHIP8

A Simple C++ implementation of the classic chip8 CPU. At this point the cpu successfully runs most games. A selection of games are available from [here](https://www.zophar.net/pdroms/chip8/chip-8-games-pack.html) for those interested.

## Dependencies
- C++17
- cmake >= 3.1

## Building
Assuming you cloned and are inside the `CHIP8` folder with a terminal you should just
```
mkdir build && cd build
cmake ..
make
```

## Usage
You have the option to run the cpu either with or without debugging.

`./chip8 <ROM_PATH>`

OR

`./chip8 <ROM_PATH> -D <DEBUG_PATH>`

Debugging is only for those interested in viewing the CPU state and memory read / write operations. To run with debugging enabled pass the `-D` flag and the path of the file you want to write to. Note that this file should not already exist.

## License
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
