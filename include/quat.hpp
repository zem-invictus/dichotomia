#pragma once
#include <cmath>
#include <type_traits>

#include "angle.hpp"
#include "dich_concepts.h"
#include "mat4.hpp"
#include "vec3.hpp"

namespace dich::math {

/**
 * @brief Quaternion template class for representing 3D rotations.
 * @tparam T Underlying scalar type (e.g., float, double).
 */
template <MathScalar T>
struct Quat {
  T x{0}; ///< Imaginary X component
  T y{0}; ///< Imaginary Y component
  T z{0}; ///< Imaginary Z component
  T w{1}; ///< Real W component

  constexpr Quat() noexcept = default;
  constexpr Quat(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}

  [[nodiscard]] friend constexpr bool operator==(Quat, Quat) noexcept = default;

  /**
   * @brief Creates a quaternion from an axis and an angle.
   * @param axis The rotation axis (should be normalized).
   * @param angle The rotation angle in radians.
   * @return A new quaternion representing the rotation.
   */
  [[nodiscard]] static Quat FromAxisAngle(Vec3<T> axis,
                                          Radians<T> angle) noexcept
    requires std::floating_point<T>
  {
    const T half_angle = angle.value / T{2};
    const T s = std::sin(half_angle);
    const T c = std::cos(half_angle);
    return {axis.x * s, axis.y * s, axis.z * s, c};
  }

  /**
   * @brief Creates a quaternion from Euler angles (Pitch, Yaw, Roll).
   * @param pitch Rotation around X axis.
   * @param yaw Rotation around Y axis.
   * @param roll Rotation around Z axis.
   * @return A new quaternion representing the combined rotation.
   */
  [[nodiscard]] static Quat FromEuler(Radians<T> pitch, Radians<T> yaw,
                                      Radians<T> roll) noexcept 
    requires std::floating_point<T>
  {
    const T cp = std::cos(pitch.value * T{0.5});
    const T sp = std::sin(pitch.value * T{0.5});
    const T cy = std::cos(yaw.value * T{0.5});
    const T sy = std::sin(yaw.value * T{0.5});
    const T cr = std::cos(roll.value * T{0.5});
    const T sr = std::sin(roll.value * T{0.5});

    return {sp * cy * cr - cp * sy * sr, cp * sy * cr + sp * cy * sr,
            cp * cy * sr - sp * sy * cr, cp * cy * cr + sp * sy * sr};
  }

  /**
   * @brief Spherical linear interpolation between two quaternions.
   * @param q1 Starting quaternion.
   * @param q2 Ending quaternion.
   * @param t Interpolation factor [0, 1].
   * @return Interpolated quaternion.
   */
  [[nodiscard]] static Quat Slerp(Quat q1, Quat q2, T t) noexcept 
    requires std::floating_point<T>
  {
    T cos_omega = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

    if (cos_omega < 0) {
      q2 = {-q2.x, -q2.y, -q2.z, -q2.w};
      cos_omega = -cos_omega;
    }

    if (cos_omega > T{0.9995}) {
      Quat res{q1.x + t * (q2.x - q1.x), q1.y + t * (q2.y - q1.y),
               q1.z + t * (q2.z - q1.z), q1.w + t * (q2.w - q1.w)};
      return res.Normalize();
    }

    T sin_omega = std::sqrt(T{1} - cos_omega * cos_omega);
    T omega = std::acos(cos_omega);

    T k1 = std::sin((T{1} - t) * omega) / sin_omega;
    T k2 = std::sin(t * omega) / sin_omega;

    return {q1.x * k1 + q2.x * k2, q1.y * k1 + q2.y * k2, q1.z * k1 + q2.z * k2,
            q1.w * k1 + q2.w * k2};
  }

  /**
   * @brief Converts the quaternion to a 4x4 rotation matrix.
   * @return A 4x4 rotation matrix.
   */
  [[nodiscard]] constexpr Mat4<T> ToMat4(this Quat self) noexcept 
    requires std::floating_point<T>
  {
    Mat4<T> res = Mat4<T>::Identity();

    const T xx = self.x * self.x;
    const T yy = self.y * self.y;
    const T zz = self.z * self.z;
    const T xy = self.x * self.y;
    const T xz = self.x * self.z;
    const T yz = self.y * self.z;
    const T wx = self.w * self.x;
    const T wy = self.w * self.y;
    const T wz = self.w * self.z;
    res.cols[0][0] = T{1} - T{2} * (yy + zz);
    res.cols[0][1] = T{2} * (xy + wz);
    res.cols[0][2] = T{2} * (xz - wy);
    res.cols[1][0] = T{2} * (xy - wz);
    res.cols[1][1] = T{1} - T{2} * (xx + zz);
    res.cols[1][2] = T{2} * (yz + wx);
    res.cols[2][0] = T{2} * (xz + wy);
    res.cols[2][1] = T{2} * (yz - wx);
    res.cols[2][2] = T{1} - T{2} * (xx + yy);
    return res;
  }

  [[nodiscard]] T Length(this Quat self) noexcept
    requires std::floating_point<T>
  {
    return std::sqrt(self.x * self.x + self.y * self.y + self.z * self.z +
                     self.w * self.w);
  }

  [[nodiscard]] constexpr T LengthSquared(this Quat self) noexcept {
    return self.x * self.x + self.y * self.y + self.z * self.z +
           self.w * self.w;
  }

  Quat& Normalize() noexcept
    requires std::floating_point<T>
  {
    const T len = Length();
    DICHOTOMIA_EXPECTS(len > T{0});
    x /= len;
    y /= len;
    z /= len;
    w /= len;
    return *this;
  }

  [[nodiscard]] Quat Normalized(this Quat self) noexcept
    requires std::floating_point<T>
  {
    const T len = self.Length();
    DICHOTOMIA_EXPECTS(len > T{0});
    return {self.x / len, self.y / len, self.z / len, self.w / len};
  }

  [[nodiscard]] constexpr Quat Conjugate(this Quat self) noexcept {
    return {-self.x, -self.y, -self.z, self.w};
  }

  [[nodiscard]] Quat Inverse(this Quat self) noexcept
    requires std::floating_point<T>
  {
    const T len_sq = self.LengthSquared();
    DICHOTOMIA_EXPECTS(len_sq > T{0});
    const T inv_len_sq = T{1} / len_sq;
    return {-self.x * inv_len_sq, -self.y * inv_len_sq, -self.z * inv_len_sq, self.w * inv_len_sq};
  }

  /**
   * @brief Multiplies two quaternions (combines rotations).
   * @param lhs The left quaternion.
   * @param rhs The right quaternion.
   * @return The combined rotation quaternion.
   */
  [[nodiscard]] friend constexpr Quat operator*(Quat lhs, Quat rhs) noexcept {
    return {lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
            lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
            lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z};
  }

  /**
   * @brief Rotates a 3D vector using this quaternion.
   * @param lhs The quaternion representing the rotation.
   * @param rhs The vector to be rotated.
   * @return The rotated vector.
   */
  [[nodiscard]] friend constexpr Vec3<T> operator*(Quat lhs, Vec3<T> rhs) noexcept {
    const Vec3<T> q_vec{lhs.x, lhs.y, lhs.z};
    const Vec3<T> t = T{2} * q_vec.Cross(rhs);
    return rhs + lhs.w * t + q_vec.Cross(t);
  }
};

using Quatf = Quat<float>;
using Quatd = Quat<double>;

static_assert(std::is_trivially_copyable_v<Quatf>, "Quatf implementation is broken!");
static_assert(std::is_trivially_copyable_v<Quatd>, "Quatd implementation is broken!");
static_assert(sizeof(Quatf) == sizeof(float) * 4, "Quatf has padding issues!");
static_assert(alignof(Quatf) == alignof(float), "Quatf alignment is broken!");
static_assert(sizeof(Quatd) == sizeof(double) * 4, "Quatd has padding issues!");
static_assert(alignof(Quatd) == alignof(double), "Quatd alignment is broken!");

}  // namespace dich::math