# ANOTE

Small utility for building code comments compatible with doxygen. It actually works with C++ and Python codes.

![anote logo](art/anote_icon.png)

## Releases
Download latest release from the [release](https://github.com/lucsch/anote/releases/latest) page.

## Build instructions
You will need the following tools :

- A recent compiler for C++
- Conan (https://conan.io)
- CMake

### Install the libraries

    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
    mkir cmake-build-debug && cd cmake-build-debug
    conan install .. -s build_type=Release

### Create and build the Project / Solution

- Windows:
  
        cmake .. -G "Visual Studio 16 2019" -A x64
        cmake --build . --config Release 

- Unix / OSX

        cmake .. 
        cmake --build

