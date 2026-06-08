from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class AnoteRecipe(ConanFile):
    name = "anote"
    version = "3.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("wxwidgets/3.3.2")
        if self.settings.os == "Linux":
            # conflict between wxwidgets 3.3.2 and libtiff/4.6.0
            self.requires("libwebp/1.6.0", override=True)
            # Force l'utilisation d'une version récente de libgpg-error requise par libgcrypt
            self.requires("libgpg-error/1.61", override=True)

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
