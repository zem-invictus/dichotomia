#include <gtest/gtest.h>
#include "mat4.hpp"

using namespace dich::math;

TEST(Mat4Test, Identity) {
  Mat4f m = Mat4f::Identity();
  EXPECT_FLOAT_EQ((m[0, 0]), 1.0f);
  EXPECT_FLOAT_EQ((m[1, 1]), 1.0f);
  EXPECT_FLOAT_EQ((m[2, 2]), 1.0f);
  EXPECT_FLOAT_EQ((m[3, 3]), 1.0f);
  EXPECT_FLOAT_EQ((m[0, 1]), 0.0f);
}

TEST(Mat4Test, Translation) {
  Mat4f m = Mat4f::Translation({1.0f, 2.0f, 3.0f});
  Vec4f v{0.0f, 0.0f, 0.0f, 1.0f};
  Vec4f res = m * v;
  EXPECT_FLOAT_EQ(res.x, 1.0f);
  EXPECT_FLOAT_EQ(res.y, 2.0f);
  EXPECT_FLOAT_EQ(res.z, 3.0f);
  EXPECT_FLOAT_EQ(res.w, 1.0f);
}

TEST(Mat4Test, DeterminantAndInverse) {
  Mat4f m = Mat4f::Scale(Vec3f{2.0f, 2.0f, 2.0f});
  EXPECT_FLOAT_EQ(m.Determinant(), 8.0f);

  Mat4f inv = m.Inverse();
  EXPECT_FLOAT_EQ((inv[0, 0]), 0.5f);
  EXPECT_FLOAT_EQ((inv[1, 1]), 0.5f);
  EXPECT_FLOAT_EQ((inv[2, 2]), 0.5f);
  EXPECT_FLOAT_EQ((inv[3, 3]), 1.0f);

  Mat4f identity = m * inv;
  EXPECT_FLOAT_EQ((identity[0, 0]), 1.0f);
  EXPECT_FLOAT_EQ((identity[1, 1]), 1.0f);
  EXPECT_FLOAT_EQ((identity[2, 2]), 1.0f);
  EXPECT_FLOAT_EQ((identity[3, 3]), 1.0f);
}

TEST(Mat4Test, LookAt) {
  Mat4f view = Mat4f::LookAt({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f});
  EXPECT_FLOAT_EQ((view[0, 0]), 1.0f);
  EXPECT_FLOAT_EQ((view[1, 1]), 1.0f);
  EXPECT_FLOAT_EQ((view[2, 2]), 1.0f);
  EXPECT_FLOAT_EQ((view[3, 3]), 1.0f);
}
