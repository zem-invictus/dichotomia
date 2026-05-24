#include <nanobind/nanobind.h>

namespace nb = nanobind;

void bind_vectors(nb::module_& m);
void bind_matrices(nb::module_& m);
void bind_quaternions(nb::module_& m);

NB_MODULE(dichotomia, m) {
    m.doc() = "Dichotomia C++23 math library python bindings";
    bind_vectors(m);
    bind_matrices(m);
    bind_quaternions(m);
}
