from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class AnoteRecipe(ConanFile):
    name = "anote"
    version = "3.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("wxwidgets/3.3.3")
        # Match the dependency versions used by ConanCenter's wxWidgets binaries.
        # Newer minor versions change package IDs, even with the same profiles.
        self.requires("expat/2.8.5", override=True)
        if self.settings.os == "Linux":
            self.requires("libcurl/8.21.0", override=True)

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
