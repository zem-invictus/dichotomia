#pragma once
#include <cmath>
#include <type_traits>
#include <utility>

#include "dich_assert.h"
#include "dich_concepts.h"

namespace dich::math {

template <MathScalar T>
struct Vec2 {
  T x{0};
  T y{0};

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
    DICHOTOMIA_EXPECTS(scalar != T{0});
    x /= scalar;
    y /= scalar;
    return *this;
  }

  [[nodiscard]] friend constexpr Vec2 operator+(Vec2 lhs, Vec2 rhs) noexcept {
    lhs += rhs;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec2 operator-(Vec2 lhs, Vec2 rhs) noexcept {
    lhs -= rhs;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec2 operator*(Vec2 lhs, T scalar) noexcept {
    lhs *= scalar;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec2 operator*(T scalar, Vec2 rhs) noexcept {
    rhs *= scalar;
    return rhs;
  }

  [[nodiscard]] friend constexpr Vec2 operator/(Vec2 lhs, T scalar) noexcept {
    lhs /= scalar;
    return lhs;
  }

  [[nodiscard]] constexpr Vec2 operator-(this Vec2 self) noexcept {
    return {-self.x, -self.y};
  }

  [[nodiscard]] constexpr T operator[](size_t ind) const noexcept {
    DICHOTOMIA_EXPECTS(ind < 2);
    switch (ind) {
      case 0:
        return x;
      case 1:
        return y;
      default:
        std::unreachable();
    }
  }

  [[nodiscard]] constexpr T& operator[](size_t ind) noexcept {
    DICHOTOMIA_EXPECTS(ind < 2);
    switch (ind) {
      case 0:
        return x;
      case 1:
        return y;
      default:
        std::unreachable();
    }
  }

  [[nodiscard]] constexpr T Dot(this Vec2 self, Vec2 rhs) noexcept {
    return self.x * rhs.x + self.y * rhs.y;
  }

  [[nodiscard]] constexpr T Cross(this Vec2 self, Vec2 rhs) noexcept {
    return self.x * rhs.y - self.y * rhs.x;
  }

  [[nodiscard]] T Length(this Vec2 self) noexcept
    requires std::floating_point<T>
  {
    return std::sqrt(self.x * self.x + self.y * self.y);
  }

  [[nodiscard]] constexpr T LengthSquared(this Vec2 self) noexcept {
    return self.x * self.x + self.y * self.y;
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
static_assert(alignof(Vec2i) == alignof(int), "Vec2i alignment is broken!");

static_assert(sizeof(Vec2f) == sizeof(float) * 2, "Vec2f has padding issues!");
static_assert(alignof(Vec2f) == alignof(float), "Vec2f alignment is broken!");

static_assert(sizeof(Vec2d) == sizeof(double) * 2, "Vec2d has padding issues!");
static_assert(alignof(Vec2d) == alignof(double), "Vec2d alignment is broken!");

static_assert(sizeof(Vec2u) == sizeof(unsigned int) * 2,
              "Vec2u has padding issues!");
static_assert(alignof(Vec2u) == alignof(unsigned int),
              "Vec2u alignment is broken!");

}  // namespace dich
