# ANOTE

Small utility for building code comments compatible with doxygen. It actually works with C++ and Python codes.

![anote logo](art/Anote_icon.png)

## Releases
Download latest release from the [release](https://github.com/lucsch/anote/releases/latest) page.

## Build instructions
You will need the following tools :

- A recent compiler for C++
- vcpkg (https://vcpkg.io/en/)
- CMake

### Create and build the Project / Solution

    mkdir cmake-build-release && cd cmake-build-release
    cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake 
    cmake --build [build directory]

### Screenshot

Anote GTK2 vs GTK3

![GTK](doc/screenshots/gtk2-vs-gtk3.png)
