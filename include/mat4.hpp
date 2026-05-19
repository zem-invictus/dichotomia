#pragma once

#include "angle.hpp"
#include "dich_concepts.h"
#include "vec3.hpp"
#include "vec4.hpp"

namespace dich::math {
template <MathScalar T>
struct Mat4 {
  Vec4<T> cols[4];

  [[nodiscard]] static constexpr Mat4 Identity() noexcept {
    return {.cols = {{T{1}, T{0}, T{0}, T{0}},
                     {T{0}, T{1}, T{0}, T{0}},
                     {T{0}, T{0}, T{1}, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  [[nodiscard]] static Mat4 RotationX(Radians<T> rads) noexcept {
    const T s = std::sin(rads.value);
    const T c = std::cos(rads.value);
    return {.cols = {{T{1}, T{0}, T{0}, T{0}},
                     {T{0}, c, s, T{0}},
                     {T{0}, -s, c, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  [[nodiscard]] static Mat4 RotationY(Radians<T> rads) noexcept {
    const T s = std::sin(rads.value);
    const T c = std::cos(rads.value);
    return {.cols = {{c, T{0}, -s, T{0}},
                     {T{0}, T{1}, T{0}, T{0}},
                     {s, T{0}, c, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  [[nodiscard]] static Mat4 RotationZ(Radians<T> rads) noexcept {
    const T s = std::sin(rads.value);
    const T c = std::cos(rads.value);
    return {.cols = {{c, s, T{0}, T{0}},
                     {-s, c, T{0}, T{0}},
                     {T{0}, T{0}, T{1}, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  [[nodiscard]] static constexpr Mat4 Translation(Vec3<T> trans) noexcept {
    return {.cols = {{T{1}, T{0}, T{0}, T{0}},
                     {T{0}, T{1}, T{0}, T{0}},
                     {T{0}, T{0}, T{1}, T{0}},
                     {trans.x, trans.y, trans.z, T{1}}}};
  }

  [[nodiscard]] static constexpr Mat4 Scale(T scale) noexcept {
    return {.cols = {{scale, T{0}, T{0}, T{0}},
                     {T{0}, scale, T{0}, T{0}},
                     {T{0}, T{0}, scale, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  [[nodiscard]] static constexpr Mat4 Scale(Vec3<T> scale) noexcept {
    return {.cols = {{scale.x, T{0}, T{0}, T{0}},
                     {T{0}, scale.y, T{0}, T{0}},
                     {T{0}, T{0}, scale.z, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  [[nodiscard]] static Mat4 Perspective(Radians<T> fovy, T aspect, T z_near, T z_far) noexcept {
    DICHOTOMIA_EXPECTS(fovy.value > T{0});
    DICHOTOMIA_EXPECTS(aspect != T{0});
    DICHOTOMIA_EXPECTS(z_near != z_far);

    const T tan_half_fovy = std::tan(fovy.value / T{2});

    Mat4 result = {};
    result.cols[0][0] = T{1} / (aspect * tan_half_fovy);
    result.cols[1][1] = T{1} / tan_half_fovy;
    result.cols[2][2] = -(z_far + z_near) / (z_far - z_near);
    result.cols[2][3] = -T{1};
    result.cols[3][2] = -(T{2} * z_far * z_near) / (z_far - z_near);

    return result;
  }

  [[nodiscard]] static constexpr Mat4 Orthographic(T left, T right, T bottom, T top, T z_near, T z_far) noexcept {
    DICHOTOMIA_EXPECTS(left != right);
    DICHOTOMIA_EXPECTS(bottom != top);
    DICHOTOMIA_EXPECTS(z_near != z_far);

    Mat4 result = Identity();
    result.cols[0][0] = T{2} / (right - left);
    result.cols[1][1] = T{2} / (top - bottom);
    result.cols[2][2] = -T{2} / (z_far - z_near);

    result.cols[3][0] = -(right + left) / (right - left);
    result.cols[3][1] = -(top + bottom) / (top - bottom);
    result.cols[3][2] = -(z_far + z_near) / (z_far - z_near);

    return result;
  }

  [[nodiscard]] static Mat4 LookAt(Vec3<T> eye, Vec3<T> center, Vec3<T> up) noexcept {
    DICHOTOMIA_EXPECTS(eye != center);
    const Vec3<T> f = (center - eye).Normalized();
    const Vec3<T> s = f.Cross(up).Normalized();
    const Vec3<T> u = s.Cross(f);

    Mat4 result = Identity();
    result.cols[0][0] = s.x;
    result.cols[1][0] = s.y;
    result.cols[2][0] = s.z;

    result.cols[0][1] = u.x;
    result.cols[1][1] = u.y;
    result.cols[2][1] = u.z;

    result.cols[0][2] = -f.x;
    result.cols[1][2] = -f.y;
    result.cols[2][2] = -f.z;

    result.cols[3][0] = -s.Dot(eye);
    result.cols[3][1] = -u.Dot(eye);
    result.cols[3][2] = f.Dot(eye);

    return result;
  }

  [[nodiscard]] constexpr T Determinant() const noexcept {
    const T a00 = cols[0][0], a01 = cols[0][1], a02 = cols[0][2], a03 = cols[0][3];
    const T a10 = cols[1][0], a11 = cols[1][1], a12 = cols[1][2], a13 = cols[1][3];
    const T a20 = cols[2][0], a21 = cols[2][1], a22 = cols[2][2], a23 = cols[2][3];
    const T a30 = cols[3][0], a31 = cols[3][1], a32 = cols[3][2], a33 = cols[3][3];

    const T b00 = a00 * a11 - a01 * a10;
    const T b01 = a00 * a12 - a02 * a10;
    const T b02 = a00 * a13 - a03 * a10;
    const T b03 = a01 * a12 - a02 * a11;
    const T b04 = a01 * a13 - a03 * a11;
    const T b05 = a02 * a13 - a03 * a12;
    const T b06 = a20 * a31 - a21 * a30;
    const T b07 = a20 * a32 - a22 * a30;
    const T b08 = a20 * a33 - a23 * a30;
    const T b09 = a21 * a32 - a22 * a31;
    const T b10 = a21 * a33 - a23 * a31;
    const T b11 = a22 * a33 - a23 * a32;

    return b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
  }

  [[nodiscard]] constexpr Mat4 Inverse() const noexcept {
    const T a00 = cols[0][0], a01 = cols[0][1], a02 = cols[0][2], a03 = cols[0][3];
    const T a10 = cols[1][0], a11 = cols[1][1], a12 = cols[1][2], a13 = cols[1][3];
    const T a20 = cols[2][0], a21 = cols[2][1], a22 = cols[2][2], a23 = cols[2][3];
    const T a30 = cols[3][0], a31 = cols[3][1], a32 = cols[3][2], a33 = cols[3][3];

    const T b00 = a00 * a11 - a01 * a10;
    const T b01 = a00 * a12 - a02 * a10;
    const T b02 = a00 * a13 - a03 * a10;
    const T b03 = a01 * a12 - a02 * a11;
    const T b04 = a01 * a13 - a03 * a11;
    const T b05 = a02 * a13 - a03 * a12;
    const T b06 = a20 * a31 - a21 * a30;
    const T b07 = a20 * a32 - a22 * a30;
    const T b08 = a20 * a33 - a23 * a30;
    const T b09 = a21 * a32 - a22 * a31;
    const T b10 = a21 * a33 - a23 * a31;
    const T b11 = a22 * a33 - a23 * a32;

    const T det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
    DICHOTOMIA_EXPECTS(det != T{0});

    const T inv_det = T{1} / det;

    Mat4 res;
    res.cols[0][0] = (a11 * b11 - a12 * b10 + a13 * b09) * inv_det;
    res.cols[0][1] = (a02 * b10 - a01 * b11 - a03 * b09) * inv_det;
    res.cols[0][2] = (a31 * b05 - a32 * b04 + a33 * b03) * inv_det;
    res.cols[0][3] = (a22 * b04 - a21 * b05 - a23 * b03) * inv_det;

    res.cols[1][0] = (a12 * b08 - a10 * b11 - a13 * b07) * inv_det;
    res.cols[1][1] = (a00 * b11 - a02 * b08 + a03 * b07) * inv_det;
    res.cols[1][2] = (a32 * b02 - a30 * b05 - a33 * b01) * inv_det;
    res.cols[1][3] = (a20 * b05 - a22 * b02 + a23 * b01) * inv_det;

    res.cols[2][0] = (a10 * b10 - a11 * b08 + a13 * b06) * inv_det;
    res.cols[2][1] = (a01 * b08 - a00 * b10 - a03 * b06) * inv_det;
    res.cols[2][2] = (a30 * b04 - a31 * b02 + a33 * b00) * inv_det;
    res.cols[2][3] = (a21 * b02 - a20 * b04 - a23 * b00) * inv_det;

    res.cols[3][0] = (a11 * b07 - a10 * b09 - a12 * b06) * inv_det;
    res.cols[3][1] = (a00 * b09 - a01 * b07 + a02 * b06) * inv_det;
    res.cols[3][2] = (a31 * b01 - a30 * b03 - a32 * b00) * inv_det;
    res.cols[3][3] = (a20 * b03 - a21 * b01 + a22 * b00) * inv_det;

    return res;
  }

  [[nodiscard]] friend constexpr Vec4<T> operator*(const Mat4& lhs,
                                                   Vec4<T> rhs) noexcept {
    return lhs.cols[0] * rhs.x + lhs.cols[1] * rhs.y + lhs.cols[2] * rhs.z +
           lhs.cols[3] * rhs.w;
  }

  [[nodiscard]] friend constexpr Mat4 operator*(const Mat4& lhs,
                                                const Mat4& rhs) noexcept {
    return {.cols = {lhs * rhs.cols[0], lhs * rhs.cols[1], lhs * rhs.cols[2],
                     lhs * rhs.cols[3]}};
  }

  [[nodiscard]] constexpr T& operator[](size_t col, size_t row) noexcept {
    DICHOTOMIA_EXPECTS(col < 4);
    DICHOTOMIA_EXPECTS(row < 4);
    return cols[col][row];
  }

  [[nodiscard]] constexpr T operator[](size_t col, size_t row) const noexcept {
    DICHOTOMIA_EXPECTS(col < 4);
    DICHOTOMIA_EXPECTS(row < 4);
    return cols[col][row];
  }

  [[nodiscard]] T* data() noexcept { return &cols[0][0]; }
  [[nodiscard]] const T* data() const noexcept { return &cols[0][0]; }
};

using Mat4f = Mat4<float>;
using Mat4d = Mat4<double>;

}  // namespace dich::math