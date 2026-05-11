include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0 # Актуальная стабильная версия
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)


#add_executable(test_vec3 test_vec3.cpp)

#target_link_libraries(test_vec3 PRIVATE
#        zem::math
#        GTest::gtest_main
#)

include(GoogleTest)
#gtest_discover_tests(test_vec3)