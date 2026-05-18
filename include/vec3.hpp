#pragma once
#include <cmath>
#include <utility>

#include "dich_assert.h"
#include "dich_concepts.h"

namespace dich::math {
template <MathScalar T>
struct Vec3 {
  T x{0};
  T y{0};
  T z{0};

  [[nodiscard]] friend constexpr bool operator==(Vec3, Vec3) noexcept = default;

  constexpr Vec3& operator+=(Vec3 rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  constexpr Vec3& operator-=(Vec3 rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  constexpr Vec3& operator*=(T scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  constexpr Vec3& operator/=(T scalar) noexcept {
    DICHOTOMIA_EXPECTS(scalar != T{0});
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  [[nodiscard]] friend constexpr Vec3 operator+(Vec3 lhs, Vec3 rhs) noexcept {
    lhs += rhs;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec3 operator-(Vec3 lhs, Vec3 rhs) noexcept {
    lhs -= rhs;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec3 operator*(Vec3 lhs, T scalar) noexcept {
    lhs *= scalar;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec3 operator*(T scalar, Vec3 lhs) noexcept {
    lhs *= scalar;
    return lhs;
  }

  [[nodiscard]] friend constexpr Vec3 operator/(Vec3 lhs, T scalar) noexcept {
    lhs /= scalar;
    return lhs;
  }

  [[nodiscard]] constexpr Vec3 operator-(this Vec3 self) noexcept {
    return {-self.x, -self.y, -self.z};
  }

  [[nodiscard]] constexpr T operator[](size_t ind) const noexcept {
    DICHOTOMIA_EXPECTS(ind < 3);
    switch (ind) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        std::unreachable();
    }
  }

  [[nodiscard]] constexpr T& operator[](size_t ind) noexcept {
    DICHOTOMIA_EXPECTS(ind < 3);
    switch (ind) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        std::unreachable();
    }
  }

  [[nodiscard]] constexpr T Dot(this Vec3 self, Vec3 rhs) noexcept {
    return self.x * rhs.x + self.y * rhs.y + self.z * rhs.z;
  }

  [[nodiscard]] constexpr Vec3 Cross(this Vec3 self, Vec3 rhs) noexcept {
    return {.x = self.y * rhs.z - self.z * rhs.y,
            .y = self.z * rhs.x - self.x * rhs.z,
            .z = self.x * rhs.y - self.y * rhs.x};
  }

  [[nodiscard]] constexpr T Length(this Vec3 self) noexcept
    requires std::floating_point<T>
  {
    return std::sqrt(self.x * self.x + self.y * self.y + self.z * self.z);
  }

  [[nodiscard]] constexpr T LengthSquared(this Vec3 self) noexcept {
    return self.x * self.x + self.y * self.y + self.z * self.z;
  }

  constexpr Vec3& Normalize() noexcept
    requires std::floating_point<T>
  {
    const T len = Length();
    DICHOTOMIA_EXPECTS(len > T{0});
    x /= len;
    y /= len;
    z /= len;
    return *this;
  }

  [[nodiscard]] constexpr Vec3 Normalized(this Vec3 self) noexcept
    requires std::floating_point<T>
  {
    const T len = self.Length();
    DICHOTOMIA_EXPECTS(len > T{0});
    return {self.x / len, self.y / len, self.z / len};
  }
};

using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3u = Vec3<unsigned int>;

static_assert(std::is_trivially_copyable_v<Vec3i>,
              "Vec3 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec3f>,
              "Vec3 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec3d>,
              "Vec3 implementation is broken!");
static_assert(std::is_trivially_copyable_v<Vec3u>,
              "Vec3 implementation is broken!");

static_assert(sizeof(Vec3i) == sizeof(int) * 3, "Vec3i has padding issues!");
static_assert(alignof(Vec3i) == alignof(int), "Vec3i alignment is broken!");

static_assert(sizeof(Vec3f) == sizeof(float) * 3, "Vec3f has padding issues!");
static_assert(alignof(Vec3f) == alignof(float), "Vec3f alignment is broken!");

static_assert(sizeof(Vec3d) == sizeof(double) * 3, "Vec3d has padding issues!");
static_assert(alignof(Vec3d) == alignof(double), "Vec3d alignment is broken!");

static_assert(sizeof(Vec3u) == sizeof(unsigned int) * 3,
              "Vec3u has padding issues!");
static_assert(alignof(Vec3u) == alignof(unsigned int),
              "Vec3u alignment is broken!");
}  // namespace dich
