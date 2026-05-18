#include <gtest/gtest.h>
#include "angle.hpp"

using namespace dich::math;

TEST(AngleTest, Conversions) {
  Radians<float> r = ToRadians(Degrees<float>(180.0f));
  EXPECT_NEAR(r.value, 3.14159265f, 1e-5f);

  Degrees<float> d = ToDegrees(Radians<float>(3.14159265f));
  EXPECT_NEAR(d.value, 180.0f, 1e-4f);
}

TEST(AngleTest, Literals) {
  using namespace dich::math::literals;
  Degrees<float> d = 180.0_deg;
  EXPECT_FLOAT_EQ(d.value, 180.0f);
  
  Radians<float> r = 3.14159265_rad;
  EXPECT_NEAR(r.value, 3.14159265f, 1e-5f);
}
