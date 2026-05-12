#pragma once
#include <cmath>
#include <type_traits>

#include "math_assert.h"
#include "math_concepts.h"

namespace zem::math {

template <typename T>
  requires MathScalar<T>
struct Vec2 {
  T x{0};
  T y{0};

  constexpr Vec2() = default;
  constexpr Vec2(T x, T y) noexcept : x(x), y(y) {}

  [[nodiscard]] friend constexpr bool operator==(Vec2, Vec2) noexcept = default;

  constexpr Vec2& operator+=(Vec2 rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  constexpr Vec2& operator-=(Vec2 rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  constexpr Vec2& operator*=(T scalar) noexcept {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  constexpr Vec2& operator/=(T scalar) noexcept {
    ZEM_MATH_EXPECTS(scalar != T{0});
    x /= scalar;
    y /= scalar;
    return *this;
  }

  [[nodiscard]] friend constexpr Vec2 operator+(Vec2 lhs, Vec2 rhs) noexcept {
    return lhs += rhs;
  }

  [[nodiscard]] friend constexpr Vec2 operator-(Vec2 lhs, Vec2 rhs) noexcept {
    return lhs -= rhs;
  }

  [[nodiscard]] friend constexpr Vec2 operator*(Vec2 lhs, T scalar) noexcept {
    return lhs *= scalar;
  }

  [[nodiscard]] friend constexpr Vec2 operator*(T scalar, Vec2 rhs) noexcept {
    return rhs *= scalar;
  }

  [[nodiscard]] friend constexpr Vec2 operator/(Vec2 lhs, T scalar) noexcept {
    return lhs /= scalar;
  }

  [[nodiscard]] constexpr Vec2 operator-() const noexcept { return {-x, -y}; }

  [[nodiscard]] constexpr T Dot(Vec2 r) const noexcept {
    return x * r.x + y * r.y;
  }

  [[nodiscard]] T Length() const noexcept
    requires std::floating_point<T>
  {
    return std::sqrt(x * x + y * y);
  }

  [[nodiscard]] constexpr T LengthSquared() const noexcept {
    return x * x + y * y;
  }
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2u = Vec2<unsigned int>;

static_assert(std::is_trivially_copyable_v<Vec2i>,
              "Vec2 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec2f>,
              "Vec2 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec2d>,
              "Vec2 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec2u>,
              "Vec2 implementation is broken!");

static_assert(sizeof(Vec2i) == sizeof(int) * 2, "Vec2i has padding issues!");
static_assert(sizeof(Vec2f) == sizeof(float) * 2, "Vec2f has padding issues!");
static_assert(sizeof(Vec2d) == sizeof(double) * 2, "Vec2d has padding issues!");
static_assert(sizeof(Vec2u) == sizeof(unsigned int) * 2,
              "Vec2u has padding issues!");

}  // namespace zem::math
