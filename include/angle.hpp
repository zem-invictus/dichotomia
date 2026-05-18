#pragma once
#include <numbers>

#include "dich_concepts.h"

namespace dich::math {

template <MathScalar T>
struct Radians {
  T value = T{0};

  constexpr Radians() noexcept = default;
  explicit constexpr Radians(T v) noexcept : value(v) {}
};

template <MathScalar T>
struct Degrees {
  T value = T{0};

  constexpr Degrees() noexcept = default;
  explicit constexpr Degrees(T v) noexcept : value(v) {}
};

template <MathScalar T>
[[nodiscard]] constexpr Degrees<T> ToDegrees(Radians<T> radians) noexcept {
  return Degrees(radians.value * (T{180} / std::numbers::pi_v<T>));
}

template <MathScalar T>
[[nodiscard]] constexpr Radians<T> ToRadians(Degrees<T> degrees) noexcept {
  return Radians(degrees.value * (std::numbers::pi_v<T> / T{180}));
}

namespace literals {

[[nodiscard]] constexpr Radians<float> operator""_rad(
    long double val) noexcept {
  return Radians(static_cast<float>(val));
}

[[nodiscard]] constexpr Degrees<float> operator""_deg(
    long double val) noexcept {
  return Degrees(static_cast<float>(val));
}

[[nodiscard]] constexpr Radians<float> operator""_rad(
    unsigned long long val) noexcept {
  return Radians(static_cast<float>(val));
}

[[nodiscard]] constexpr Degrees<float> operator""_deg(
    unsigned long long val) noexcept {
  return Degrees(static_cast<float>(val));
}

}  // namespace literals

}  // namespace dich::math