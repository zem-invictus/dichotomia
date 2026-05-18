#include <gtest/gtest.h>
#include "vec4.hpp"

using namespace dich::math;

TEST(Vec4Test, InitializationAndEquality) {
  Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
  Vec4f v2{1.0f, 2.0f, 3.0f, 4.0f};
  Vec4f v3{0.0f, 2.0f, 3.0f, 4.0f};

  EXPECT_EQ(v1, v2);
  EXPECT_NE(v1, v3);
  EXPECT_EQ(v1.x, 1.0f);
  EXPECT_EQ(v1.w, 4.0f);
}

TEST(Vec4Test, ArithmeticOperations) {
  Vec4f v1{2.0f, 3.0f, 4.0f, 5.0f};
  Vec4f v2{1.0f, 1.0f, 1.0f, 1.0f};

  Vec4f sum = v1 + v2;
  EXPECT_EQ(sum.x, 3.0f);
  EXPECT_EQ(sum.w, 6.0f);

  Vec4f diff = v1 - v2;
  EXPECT_EQ(diff.x, 1.0f);
  EXPECT_EQ(diff.w, 4.0f);
}

TEST(Vec4Test, LengthAndNormalization) {
  Vec4f v{0.0f, 0.0f, 3.0f, 4.0f};
  EXPECT_FLOAT_EQ(v.Length(), 5.0f);

  Vec4f norm = v.Normalized();
  EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
  EXPECT_FLOAT_EQ(norm.w, 0.8f);
}
