#include <gtest/gtest.h>
#include "vec2.hpp"

using namespace dich::math;

TEST(Vec2Test, InitializationAndEquality) {
  Vec2f v1{1.0f, 2.0f};
  Vec2f v2{1.0f, 2.0f};
  Vec2f v3{0.0f, 2.0f};

  EXPECT_EQ(v1, v2);
  EXPECT_NE(v1, v3);
  EXPECT_EQ(v1.x, 1.0f);
  EXPECT_EQ(v1.y, 2.0f);
}

TEST(Vec2Test, ArithmeticOperations) {
  Vec2f v1{2.0f, 3.0f};
  Vec2f v2{1.0f, 4.0f};

  Vec2f sum = v1 + v2;
  EXPECT_EQ(sum.x, 3.0f);
  EXPECT_EQ(sum.y, 7.0f);

  Vec2f diff = v1 - v2;
  EXPECT_EQ(diff.x, 1.0f);
  EXPECT_EQ(diff.y, -1.0f);

  Vec2f mul = v1 * 2.0f;
  EXPECT_EQ(mul.x, 4.0f);
  EXPECT_EQ(mul.y, 6.0f);

  Vec2f div = v1 / 2.0f;
  EXPECT_EQ(div.x, 1.0f);
  EXPECT_EQ(div.y, 1.5f);
}

TEST(Vec2Test, LengthAndNormalization) {
  Vec2f v{3.0f, 4.0f};
  EXPECT_FLOAT_EQ(v.Length(), 5.0f);
  EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);

  Vec2f norm = v.Normalized();
  EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
  EXPECT_FLOAT_EQ(norm.x, 0.6f);
  EXPECT_FLOAT_EQ(norm.y, 0.8f);

  v.Normalize();
  EXPECT_FLOAT_EQ(v.Length(), 1.0f);
}

TEST(Vec2Test, DotProduct) {
  Vec2f v1{1.0f, 0.0f};
  Vec2f v2{0.0f, 1.0f};
  EXPECT_FLOAT_EQ(v1.Dot(v2), 0.0f);

  Vec2f v3{2.0f, 3.0f};
  Vec2f v4{4.0f, 5.0f};
  EXPECT_FLOAT_EQ(v3.Dot(v4), 23.0f);
}
