# ANOTE

Small utility for building code comments compatible with doxygen. It actually works with C++ and Python codes.

![anote logo](art/Anote_icon.png)

## Releases
Download latest release from the [release](https://github.com/lucsch/anote/releases/latest) page.

## Build instructions
You will need the following tools :

- A recent compiler for C++
- Conan (https://conan.io)
- CMake

### Install the libraries

    conan remote add gitlab https://gitlab.com/api/v4/packages/conan
    conan user gitlab+deploy-token-653038 -r gitlab -p sBwmejFz5Pn-gZPSNFMy
    conan profile update settings.compiler.libcxx=libstdc++11 default
    conan install .. 

### Create and build the Project / Solution

    mkdir cmake-build-release && cd cmake-build-release
    conan build .. or conan build .. -s build_type=Debug

### Screenshot

Anote GTK2 vs GTK3

![GTK](doc/screenshots/gtk2-vs-gtk3.png)
