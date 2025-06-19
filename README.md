# Spinarak
A work-in-progress GameBoy emulator written in modern C++.

The goals of this project are to learn modern C++ (templates, concepts, etc.) and write modular, clean code. The project will be considered a success if Pokemon Red can be run.

## Running
If you have Taskfile, do `task init-cmake` to initiate the CMake project, and `task build` to build it. If you do not have Taskfile, either install it or
```
mkdir build && cd build
cmake ..
```
to initiate the CMake project and
```
make
```
within `build` to compile the project.

## Todo List
- [ ] Finish implementation of the CPU module
- [ ] Write unit tests using GTest (alongside above)
- [ ] Pass Blaarg's integration tests
- [ ] Draw to screen and support graphics
- [ ] Support MBCs to support larger ROMs
- [ ] Support keyboard controls
- [ ] Support audo
