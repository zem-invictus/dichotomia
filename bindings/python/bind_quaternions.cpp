#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include "dichotomia.hpp"

namespace nb = nanobind;
using namespace dich::math;

void bind_quaternions(nb::module_& m) {
    nb::class_<Quatf>(m, "Quatf")
        .def("__init__", [](Quatf *t, float x, float y, float z, float w) { new (t) Quatf{x, y, z, w}; }, nb::arg("x") = 0.0f, nb::arg("y") = 0.0f, nb::arg("z") = 0.0f, nb::arg("w") = 1.0f)
        .def_rw("x", &Quatf::x)
        .def_rw("y", &Quatf::y)
        .def_rw("z", &Quatf::z)
        .def_rw("w", &Quatf::w)
        .def_static("FromAxisAngle", [](const Vec3f& axis, float angle_rad) { return Quatf::FromAxisAngle(axis, Radians<float>{angle_rad}); }, nb::arg("axis"), nb::arg("angle_rad"))
        .def_static("FromEuler", [](float pitch_rad, float yaw_rad, float roll_rad) { 
             return Quatf::FromEuler(Radians<float>{pitch_rad}, Radians<float>{yaw_rad}, Radians<float>{roll_rad}); 
        }, nb::arg("pitch_rad"), nb::arg("yaw_rad"), nb::arg("roll_rad"))
        .def_static("Slerp", &Quatf::Slerp, nb::arg("q1"), nb::arg("q2"), nb::arg("t"))
        .def("ToMat4", &Quatf::ToMat4)
        .def("Length", &Quatf::Length)
        .def("LengthSquared", &Quatf::LengthSquared)
        .def("Normalize", &Quatf::Normalize)
        .def("Normalized", &Quatf::Normalized)
        .def("Conjugate", &Quatf::Conjugate)
        .def("Inverse", &Quatf::Inverse)
        .def(nb::self * nb::self)
        .def(nb::self * Vec3f())
        .def("__repr__", [](const Quatf& q) { return "Quatf(" + std::to_string(q.x) + ", " + std::to_string(q.y) + ", " + std::to_string(q.z) + ", " + std::to_string(q.w) + ")"; });
}
