#include "../include/dichotomia.hpp"
#include <gtest/gtest.h>

TEST(Vec3Test, DefaultConstructor) {
    dich::math::Vec3f v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, 0.0f);
}