#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <new>
#include <nanobind/ndarray.h>
#include "dichotomia.hpp"

namespace nb = nanobind;
using namespace dich::math;

void bind_matrices(nb::module_& m) {
    nb::class_<Mat4f>(m, "Mat4f")
        .def("__init__", [](Mat4f *t) { new (t) Mat4f(Mat4f::Identity()); })
        .def_static("Identity", &Mat4f::Identity)
        .def_static("RotationX", [](float rad) { return Mat4f::RotationX(Radians<float>{rad}); }, nb::arg("rad"))
        .def_static("RotationY", [](float rad) { return Mat4f::RotationY(Radians<float>{rad}); }, nb::arg("rad"))
        .def_static("RotationZ", [](float rad) { return Mat4f::RotationZ(Radians<float>{rad}); }, nb::arg("rad"))
        .def_static("Translation", [](const Vec3f& v) { return Mat4f::Translation(v); }, nb::arg("trans"))
        .def_static("Scale", [](float s) { return Mat4f::Scale(s); }, nb::arg("scale"))
        .def_static("ScaleVec", [](const Vec3f& v) { return Mat4f::Scale(v); }, nb::arg("scale"))
        .def_static("Perspective", [](float fovy, float aspect, float z_near, float z_far) { 
            return Mat4f::Perspective(Radians<float>{fovy}, aspect, z_near, z_far); 
        }, nb::arg("fovy_rad"), nb::arg("aspect"), nb::arg("z_near"), nb::arg("z_far"))
        .def_static("Orthographic", &Mat4f::Orthographic, nb::arg("left"), nb::arg("right"), nb::arg("bottom"), nb::arg("top"), nb::arg("z_near"), nb::arg("z_far"))
        .def_static("LookAt", &Mat4f::LookAt, nb::arg("eye"), nb::arg("center"), nb::arg("up"))
        .def("Determinant", &Mat4f::Determinant)
        .def("Inverse", &Mat4f::Inverse)
        .def(nb::self * nb::self)
        .def(nb::self * Vec4f())
        .def("__array__", [](Mat4f &m, nb::kwargs) {
            size_t shape[2] = {4, 4};
            int64_t strides[2] = {1, 4};
            return nb::ndarray<nb::numpy, float, nb::shape<4, 4>>(&m.cols[0].x, 2, shape, nb::cast(m), strides);
        });
}
