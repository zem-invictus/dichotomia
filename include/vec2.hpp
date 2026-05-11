//
// Created by Владимир on 11.05.2026.
//

#pragma once

namespace zem::math {
struct Vec2 {
  float x, y, z;

  constexpr Vec2& operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
};
} // namespace zem::math
