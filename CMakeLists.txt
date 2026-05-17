CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
project(dichotomia VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_library(zem::dich ALIAS dich)

target_compile_features(dichotomia INTERFACE cxx_std_23)

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
endif()