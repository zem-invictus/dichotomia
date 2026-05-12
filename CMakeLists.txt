CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
project(zem_math VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(zem_math INTERFACE
        include/math_assert.h
        include/macros.h)

add_library(zem::math ALIAS zem_math)

target_compile_features(zem_math INTERFACE cxx_std_23)

target_compile_definitions(zem_math
        INTERFACE
            $<$<CONFIG:Debug>:ZEM_MATH_DEBUG>
)

target_include_directories(zem_math INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(tests)
endif()