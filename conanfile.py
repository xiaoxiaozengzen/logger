from conan import ConanFile
from conan.tools.env import VirtualRunEnv, VirtualBuildEnv
from conan.tools.cmake import CMakeDeps, CMakeToolchain

required_conan_version = ">=1.53.0"


class LoggerConan(ConanFile):
    name = "logger"
    version = "dev"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "with_spdlog_example": [True, False],
        "with_fmt_example": [True, False],
    }
    default_options = {
        "with_spdlog_example": True,
        "with_fmt_example": True,
    }

    @property
    def _min_cppstd(self):
        return 14

    def requirements(self):
        self.requires("spdlog/1.9.2")
        if self.options.with_fmt_example:
            self.requires("fmt/8.0.1")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"
        if self.options.with_spdlog_example:
            tc.variables["WITH_SPDLOG_EXAMPLE"] = "ON"
        else:
            tc.variables["WITH_SPDLOG_EXAMPLE"] = "OFF"
        if self.options.with_fmt_example:
            tc.variables["WITH_FMT_EXAMPLE"] = "ON"
        else:
            tc.variables["WITH_FMT_EXAMPLE"] = "OFF"
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()
        tc = VirtualRunEnv(self)
        tc.generate()
        tc = VirtualBuildEnv(self)
        tc.generate(scope="build")
