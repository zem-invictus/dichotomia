#pragma once
#include <concepts>

namespace zem::math {
template <typename T>
concept MathScalar = (std::floating_point<T> || std::integral<T>) &&
                     !std::same_as<T, bool> && !std::same_as<T, char>;
}
