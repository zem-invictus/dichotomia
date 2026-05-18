#pragma once
#include <vector>

#include "angle.hpp"
#include "dich_concepts.h"
#include "vec3.hpp"
#include "vec4.hpp"

namespace dich::math {
template <MathScalar T>
struct Mat4 {
  Vec4<T> cols[4];

  [[nodiscard]] static constexpr Mat4& Identity() noexcept {
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
}  // namespace dich::math