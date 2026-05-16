#pragma once
#include <vector>

#include "math_concepts.h"
#include "vec4.hpp"

namespace zem::math {
template <MathScalar T>
struct Mat4 {
  Vec4<T> cols[4];

  [[nodiscard]] static constexpr Mat4& Identity() noexcept {
    return {.cols = {{T{1}, T{0}, T{0}, T{0}},
                     {T{0}, T{1}, T{0}, T{0}},
                     {T{0}, T{0}, T{1}, T{0}},
                     {T{0}, T{0}, T{0}, T{1}}}};
  }

  
};
}  // namespace zem::math