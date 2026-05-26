nanobind_add_module(dichotomia_py module.cpp bind_vectors.cpp bind_matrices.cpp bind_quaternions.cpp)
set_target_properties(dichotomia_py PROPERTIES OUTPUT_NAME "dichotomia")

target_link_libraries(dichotomia_py PRIVATE dichotomia::dichotomia)

nanobind_add_stub(
    dichotomia_py_stub
    MODULE dichotomia
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/dichotomia.pyi"
    DEPENDS dichotomia_py
)

# Optional: set C++23 explicitly for the binding module just in case
target_compile_features(dichotomia_py PRIVATE cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL "dichotomia")
    add_test(NAME python_bindings_test
             COMMAND Python::Interpreter -m pytest "${CMAKE_CURRENT_SOURCE_DIR}/tests")

    set_tests_properties(python_bindings_test PROPERTIES
        ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:dichotomia_py>;PYTHONUNBUFFERED=1"
    )
endif()
