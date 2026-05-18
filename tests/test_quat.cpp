#include <gtest/gtest.h>
#include "quat.hpp"
#include <numbers>

using namespace dich::math;

TEST(QuatTest, Identity) {
  Quatf q;
  EXPECT_FLOAT_EQ(q.x, 0.0f);
  EXPECT_FLOAT_EQ(q.y, 0.0f);
  EXPECT_FLOAT_EQ(q.z, 0.0f);
  EXPECT_FLOAT_EQ(q.w, 1.0f);
}

TEST(QuatTest, FromAxisAngleAndMat4) {
  Radiansf angle(std::numbers::pi_v<float> / 2.0f);
  Quatf q = Quatf::FromAxisAngle({0.0f, 1.0f, 0.0f}, angle);
  
  Mat4f m = q.ToMat4();
  Vec4f vx = m * Vec4f{1.0f, 0.0f, 0.0f, 1.0f};
  EXPECT_NEAR(vx.x, 0.0f, 1e-6f);
  EXPECT_NEAR(vx.z, -1.0f, 1e-6f);
}

TEST(QuatTest, FromEuler) {
  Radiansf yaw(std::numbers::pi_v<float> / 2.0f);
  Radiansf pitch(0.0f);
  Radiansf roll(0.0f);
  
  Quatf q = Quatf::FromEuler(pitch, yaw, roll);
  Mat4f m = q.ToMat4();
  Vec4f vx = m * Vec4f{1.0f, 0.0f, 0.0f, 1.0f};
  EXPECT_NEAR(vx.x, 0.0f, 1e-6f);
  EXPECT_NEAR(vx.z, -1.0f, 1e-6f);
}
