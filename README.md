# golpp
This is a simulation of John Conway's Game of Life (with periodic boundary conditions), written in C++, that can be run from a terminal using a text-based UI. This is made possible by the lovely [FTXUI](https://github.com/ArthurSonzogni/FTXUI) library for text-based UIs.

## Installation
The CMakeLists file is included - download the source, run cmake and then run make in the resulting build directory to generate an executable. Tested on Windows WSL2 (Debian 11.5) with g++ version 10.2.1.

## Usage
On program execution some instructions are provided. Basic usage is to left-click cells to toggle them alive/dead, then once you are satisfied with the initial board configuration, press [e] to start the simulation. At any point [e] can be pressed again to edit the board state. [q] will exit the program. [1], [2], [3] set the simulation speed to 10/20/40 fps respectively.
