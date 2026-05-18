#include <gtest/gtest.h>
#include "vec3.hpp"

using namespace dich::math;

TEST(Vec3Test, InitializationAndEquality) {
  Vec3f v1{1.0f, 2.0f, 3.0f};
  Vec3f v2{1.0f, 2.0f, 3.0f};
  Vec3f v3{0.0f, 2.0f, 3.0f};

  EXPECT_EQ(v1, v2);
  EXPECT_NE(v1, v3);
  EXPECT_EQ(v1.x, 1.0f);
  EXPECT_EQ(v1.y, 2.0f);
  EXPECT_EQ(v1.z, 3.0f);
}

TEST(Vec3Test, ArithmeticOperations) {
  Vec3f v1{2.0f, 3.0f, 4.0f};
  Vec3f v2{1.0f, 4.0f, 1.0f};

  Vec3f sum = v1 + v2;
  EXPECT_EQ(sum.x, 3.0f);
  EXPECT_EQ(sum.y, 7.0f);
  EXPECT_EQ(sum.z, 5.0f);

  Vec3f diff = v1 - v2;
  EXPECT_EQ(diff.x, 1.0f);
  EXPECT_EQ(diff.y, -1.0f);
  EXPECT_EQ(diff.z, 3.0f);

  Vec3f mul = v1 * 2.0f;
  EXPECT_EQ(mul.x, 4.0f);
  EXPECT_EQ(mul.y, 6.0f);
  EXPECT_EQ(mul.z, 8.0f);

  Vec3f div = v1 / 2.0f;
  EXPECT_EQ(div.x, 1.0f);
  EXPECT_EQ(div.y, 1.5f);
  EXPECT_EQ(div.z, 2.0f);
}

TEST(Vec3Test, LengthAndNormalization) {
  Vec3f v{0.0f, 3.0f, 4.0f};
  EXPECT_FLOAT_EQ(v.Length(), 5.0f);
  EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);

  Vec3f norm = v.Normalized();
  EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
  EXPECT_FLOAT_EQ(norm.x, 0.0f);
  EXPECT_FLOAT_EQ(norm.y, 0.6f);
  EXPECT_FLOAT_EQ(norm.z, 0.8f);

  v.Normalize();
  EXPECT_FLOAT_EQ(v.Length(), 1.0f);
}

TEST(Vec3Test, DotAndCrossProduct) {
  Vec3f v1{1.0f, 0.0f, 0.0f};
  Vec3f v2{0.0f, 1.0f, 0.0f};
  EXPECT_FLOAT_EQ(v1.Dot(v2), 0.0f);

  Vec3f cross = v1.Cross(v2);
  EXPECT_FLOAT_EQ(cross.x, 0.0f);
  EXPECT_FLOAT_EQ(cross.y, 0.0f);
  EXPECT_FLOAT_EQ(cross.z, 1.0f);
}