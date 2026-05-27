CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
project(dichotomia VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DICHOTOMIA_BUILD_PYTHON_BINDINGS "Build nanobind Python bindings" OFF)

add_library(dichotomia INTERFACE)

target_sources(dichotomia
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/macros.h
        include/dich_assert.h
        include/dich_concepts.h
        include/vec2.hpp
        include/vec3.hpp
        include/vec4.hpp
        include/mat4.hpp
        include/angle.hpp
        include/dichotomia.hpp
)

add_library(dichotomia::dichotomia ALIAS dichotomia)

target_compile_features(dichotomia INTERFACE cxx_std_23)

if(MSVC)
    target_compile_options(dichotomia INTERFACE /std:c++latest)
endif()

target_compile_definitions(dichotomia
        INTERFACE
            $<$<CONFIG:Debug>:DICHOTOMIA_DEBUG>
)

target_include_directories(dichotomia INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(tests)
    add_subdirectory(benchmarks)
endif()

if(DICHOTOMIA_BUILD_PYTHON_BINDINGS)
    find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
    include(FetchContent)
    FetchContent_Declare(
      nanobind
      GIT_REPOSITORY https://github.com/wjakob/nanobind.git
      GIT_TAG v2.4.0
    )
    FetchContent_MakeAvailable(nanobind)
    add_subdirectory(bindings/python)
endif()

# Documentation
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs ALL
        COMMAND Doxygen::doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    add_dependencies(dichotomia docs)
endif()
