#pragma once
#include <numbers>

namespace dich::math {

struct Radians {
  float value{0.0f};

  constexpr Radians() noexcept = default;
  explicit constexpr Radians(float v) noexcept : value(v) {}
};

struct Degrees {
  float value{0.0f};

  constexpr Degrees() noexcept = default;
  explicit constexpr Degrees(float v) noexcept : value(v) {}
};

[[nodiscard]] constexpr Degrees ToDegrees(Radians radians) noexcept {
  return Degrees(radians.value * (180.0f / std::numbers::pi_v<float>));
}

[[nodiscard]] constexpr Radians ToRadians(Degrees degrees) noexcept {
  return Radians(degrees.value * (std::numbers::pi_v<float> / 180.0f));
}

namespace literals {

[[nodiscard]] constexpr Radians operator""_rad(long double val) noexcept {
  return Radians(static_cast<float>(val));
}

[[nodiscard]] constexpr Degrees operator""_deg(long double val) noexcept {
  return Degrees(static_cast<float>(val));
}

[[nodiscard]] constexpr Radians operator""_rad(
    unsigned long long val) noexcept {
  return Radians(static_cast<float>(val));
}

[[nodiscard]] constexpr Degrees operator""_deg(
    unsigned long long val) noexcept {
  return Degrees(static_cast<float>(val));
}

}  // namespace literals

}  // namespace dich::math