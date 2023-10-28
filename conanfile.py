from conans import ConanFile, CMake


class Anote(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = ["wxwidgets/3.2.3@terranum-conan+wxwidgets/stable"]

    generators = "cmake", "gcc", "txt"

    def configure(self):
       if self.settings.os == "Linux":
           # self.options["wxwidgets"].webview = False # webview control isn't available on linux.
           self.options["wxwidgets"].png = "system" # use png sys lib on linux, otherwise leads to a crash.

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib")  # From lib to bin

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
