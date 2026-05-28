#pragma once
#include <numbers>

#include "dich_concepts.h"

namespace dich::math {

/**
 * @brief Type-safe wrapper for angle values in radians.
 * @tparam T Underlying scalar type (e.g., float, double).
 */
template <MathScalar T>
struct Radians {
  T value = T{0};

  constexpr Radians() noexcept = default;
  explicit constexpr Radians(T v) noexcept : value(v) {}
};

/**
 * @brief Type-safe wrapper for angle values in degrees.
 * @tparam T Underlying scalar type (e.g., float, double).
 */
template <MathScalar T>
struct Degrees {
  T value = T{0};

  constexpr Degrees() noexcept = default;
  explicit constexpr Degrees(T v) noexcept : value(v) {}
};

/**
 * @brief Converts an angle from radians to degrees.
 * @param radians Angle in radians.
 * @return Angle in degrees.
 */
template <MathScalar T>
  requires std::floating_point<T>
[[nodiscard]] constexpr Degrees<T> ToDegrees(Radians<T> radians) noexcept {
  return Degrees(radians.value * (T{180} / std::numbers::pi_v<T>));
}

/**
 * @brief Converts an angle from degrees to radians.
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
template <MathScalar T>
  requires std::floating_point<T>
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

using Radiansf = Radians<float>;
using Radiansd = Radians<double>;
using Degreesf = Degrees<float>;
using Degreesd = Degrees<double>;

}  // namespace dich::math