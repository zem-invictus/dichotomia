include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0 # Актуальная стабильная версия
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

macro(dichotomia_add_test test_name)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} PRIVATE zem::dichotomia GTest::gtest_main)
    gtest_discover_tests(${test_name})
endmacro()

dichotomia_add_test(test_angle)
dichotomia_add_test(test_vec2)
dichotomia_add_test(test_vec3)
dichotomia_add_test(test_vec4)
dichotomia_add_test(test_mat4)
dichotomia_add_test(test_quat)