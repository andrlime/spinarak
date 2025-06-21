# Spinarak
A work-in-progress GameBoy emulator written in modern C++.

The purpose of this project is to learn modern C++ (templates, concepts, etc.) and write modular, clean code. The project will be considered a success if Pokemon Red can be run.

## Running
If you have Taskfile, do `task init-conan && task init-cmake` to initiate the CMake project, and `task build` to build. If you do not have Taskfile, install it, or open the Taskfile and manually run those commands. Conan and CMake are both required for this project.

## Todo List
- [ ] Finish implementation of the CPU module
- [ ] Write unit tests using GTest (alongside above)
- [ ] Pass Blaarg's integration tests
- [ ] Draw to screen and support graphics
- [ ] Support MBCs to support larger ROMs
- [ ] Support keyboard controls
- [ ] Support audo
