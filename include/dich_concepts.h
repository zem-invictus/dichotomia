#pragma once
#include <concepts>

namespace dich::math {
/**
 * @brief Concept that restricts types to valid mathematical scalars.
 *
 * Allows floating-point types (`float`, `double`) and integral types
 * (`int`, `int32_t`, etc.), but explicitly rejects `bool` and `char` to
 * avoid unexpected implicit conversions in math operations.
 *
 * @tparam T The type to be validated.
 */
template <typename T>
concept MathScalar = (std::floating_point<T> || std::integral<T>) &&
                     !std::same_as<T, bool> && !std::same_as<T, char>;
}
