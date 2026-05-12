#pragma once
#include <utility>

#include "math_concepts.h"

namespace zem::math {
template <typename T>
  requires MathScalar<T>
struct Vec3 {
  T x{0};
  T y{0};
  T z{0};

  Vec3() = default;
  Vec3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}

  friend bool operator==(const Vec3&, const Vec3& rhs) noexcept = default;
};
}  // namespace zem::math
