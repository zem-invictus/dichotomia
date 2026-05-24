nanobind_add_module(dichotomia_py module.cpp bind_vectors.cpp bind_matrices.cpp bind_quaternions.cpp)
set_target_properties(dichotomia_py PROPERTIES OUTPUT_NAME "dichotomia")

target_link_libraries(dichotomia_py PRIVATE dichotomia::dichotomia)

# Optional: set C++23 explicitly for the binding module just in case
target_compile_features(dichotomia_py PRIVATE cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Register the python test with CTest
    add_test(NAME python_bindings_test
             COMMAND Python::Interpreter "${CMAKE_SOURCE_DIR}/tests/test_python_bindings.py")

    # Tell CTest to set the PYTHONPATH to the directory where the .pyd was built
    set_tests_properties(python_bindings_test PROPERTIES
        ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:dichotomia_py>"
    )
endif()
