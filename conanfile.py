from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout

class DichotomiaConan(ConanFile):
    name = "dichotomia"
    version = "1.0.1"
    license = "MIT"
    author = "zem-invictus"
    url = "https://github.com/zem-invictus/dichotomia"
    description = "C++23 mathematical library"
    topics = ("math", "linear-algebra", "header-only")
    settings = "os", "compiler", "build_type", "arch"
    package_type = "header-library"
    exports_sources = "CMakeLists.txt", "include/*", "cmake/*"
    no_copy_source = True

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["DICHOTOMIA_BUILD_PYTHON_BINDINGS"] = "OFF"
        tc.variables["DICHOTOMIA_BUILD_TESTING"] = "OFF"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.set_property("cmake_file_name", "dichotomia")
        self.cpp_info.set_property("cmake_target_name", "dichotomia::dichotomia")
