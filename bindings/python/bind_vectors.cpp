#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include "dichotomia.hpp"

namespace nb = nanobind;
using namespace dich::math;

void bind_vectors(nb::module_& m) {
    nb::class_<Vec2f>(m, "Vec2f")
        .def("__init__", [](Vec2f *t, float x, float y) { new (t) Vec2f{x, y}; }, nb::arg("x") = 0.0f, nb::arg("y") = 0.0f)
        .def_rw("x", &Vec2f::x)
        .def_rw("y", &Vec2f::y)
        .def(nb::self == nb::self)
        .def(nb::self + nb::self)
        .def(nb::self - nb::self)
        .def(nb::self * float())
        .def(float() * nb::self)
        .def(nb::self / float())
        .def(-nb::self)
        .def("Dot", &Vec2f::Dot)
        .def("Cross", &Vec2f::Cross)
        .def("Length", &Vec2f::Length)
        .def("LengthSquared", &Vec2f::LengthSquared)
        .def("Normalize", &Vec2f::Normalize)
        .def("Normalized", &Vec2f::Normalized)
        .def("__repr__", [](const Vec2f& v) { return "Vec2f(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")"; });

    nb::class_<Vec3f>(m, "Vec3f")
        .def("__init__", [](Vec3f *t, float x, float y, float z) { new (t) Vec3f{x, y, z}; }, nb::arg("x") = 0.0f, nb::arg("y") = 0.0f, nb::arg("z") = 0.0f)
        .def_rw("x", &Vec3f::x)
        .def_rw("y", &Vec3f::y)
        .def_rw("z", &Vec3f::z)
        .def(nb::self == nb::self)
        .def(nb::self + nb::self)
        .def(nb::self - nb::self)
        .def(nb::self * float())
        .def(float() * nb::self)
        .def(nb::self / float())
        .def(-nb::self)
        .def("Dot", &Vec3f::Dot)
        .def("Cross", &Vec3f::Cross)
        .def("Length", &Vec3f::Length)
        .def("LengthSquared", &Vec3f::LengthSquared)
        .def("Normalize", &Vec3f::Normalize)
        .def("Normalized", &Vec3f::Normalized)
        .def("__repr__", [](const Vec3f& v) { return "Vec3f(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")"; });

    nb::class_<Vec4f>(m, "Vec4f")
        .def("__init__", [](Vec4f *t, float x, float y, float z, float w) { new (t) Vec4f{x, y, z, w}; }, nb::arg("x") = 0.0f, nb::arg("y") = 0.0f, nb::arg("z") = 0.0f, nb::arg("w") = 0.0f)
        .def_rw("x", &Vec4f::x)
        .def_rw("y", &Vec4f::y)
        .def_rw("z", &Vec4f::z)
        .def_rw("w", &Vec4f::w)
        .def(nb::self == nb::self)
        .def(nb::self + nb::self)
        .def(nb::self - nb::self)
        .def(nb::self * float())
        .def(float() * nb::self)
        .def(nb::self / float())
        .def(-nb::self)
        .def("Dot", &Vec4f::Dot)
        .def("Length", &Vec4f::Length)
        .def("LengthSquared", &Vec4f::LengthSquared)
        .def("Normalize", &Vec4f::Normalize)
        .def("Normalized", &Vec4f::Normalized)
        .def("__repr__", [](const Vec4f& v) { return "Vec4f(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")"; });
}
