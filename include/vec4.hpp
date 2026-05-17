#pragma once

#include <cmath>
#include <concepts>
#include <utility>

#include "math_assert.h"
#include "math_concepts.h"

namespace zem::dich {
template <MathScalar T>
struct Vec4 {
  T x{0};
  T y{0};
  T z{0};
  T w{0};

  [[nodiscard]] friend constexpr bool operator==(Vec4, Vec4) noexcept = default;

  constexpr Vec4& operator+=(Vec4 rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  constexpr Vec4& operator-=(Vec4 rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  constexpr Vec4& operator*=(T scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  constexpr Vec4& operator/=(T scalar) noexcept {
    DICHOTOMIA_EXPECTS(scalar != T{0});
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
  }

  [[nodiscard]] friend constexpr Vec4 operator+(Vec4 lhs, Vec4 rhs) noexcept {
    lhs += rhs;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec4 operator-(Vec4 lhs, Vec4 rhs) noexcept {
    lhs -= rhs;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec4 operator*(Vec4 lhs, T scalar) noexcept {
    lhs *= scalar;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec4 operator*(T scalar, Vec4 rhs) noexcept {
    rhs *= scalar;
    return rhs;
  }

  [[nodiscard]] friend constexpr Vec4 operator/(Vec4 lhs, T scalar) noexcept {
    lhs /= scalar;
    return lhs;
  }

  [[nodiscard]] constexpr Vec4 operator-(this Vec4 self) noexcept {
    return {-self.x, -self.y, -self.z, -self.w};
  }

  [[nodiscard]] constexpr T& operator[](size_t ind) noexcept {
    DICHOTOMIA_EXPECTS(ind < 4);
    switch (ind) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
        return w;
      default:
        std::unreachable();
    }
  }

  [[nodiscard]] constexpr T operator[](size_t ind) const noexcept {
    DICHOTOMIA_EXPECTS(ind < 4);
    switch (ind) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
        return w;
      default:
        std::unreachable();
    }
  }

  [[nodiscard]] constexpr T Dot(this Vec4 self, Vec4 rhs) noexcept {
    return self.x * rhs.x + self.y * rhs.y + self.z * rhs.z + self.w * rhs.w;
  }

  [[nodiscard]] T Length(this Vec4 self) noexcept
    requires std::floating_point<T>
  {
    return std::sqrt(self.x * self.x + self.y * self.y + self.z * self.z +
                     self.w * self.w);
  }

  [[nodiscard]] constexpr T LengthSquared(this Vec4 self) noexcept {
    return self.x * self.x + self.y * self.y + self.z * self.z +
           self.w * self.w;
  }
};

using Vec4i = Vec4<int>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4u = Vec4<unsigned int>;

static_assert(std::is_trivially_copyable_v<Vec4i>,
              "Vec4 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec4f>,
              "Vec4 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec4d>,
              "Vec4 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec4u>,
              "Vec4 implementation is broken!");

static_assert(sizeof(Vec4i) == sizeof(int) * 4, "Vec4i has padding issues!");
static_assert(alignof(Vec4i) == alignof(int), "Vec4i alignment is broken!");

static_assert(sizeof(Vec4f) == sizeof(float) * 4, "Vec4f has padding issues!");
static_assert(alignof(Vec4f) == alignof(float), "Vec4f alignment is broken!");

static_assert(sizeof(Vec4d) == sizeof(double) * 4, "Vec4d has padding issues!");
static_assert(alignof(Vec4d) == alignof(double), "Vec4d alignment is broken!");

static_assert(sizeof(Vec4u) == sizeof(unsigned int) * 4,
              "Vec4u has padding issues!");
static_assert(alignof(Vec4u) == alignof(unsigned int),
              "Vec4u alignment is broken!");
}  // namespace zem::dich
