/**
 * @file macros.h
 * @brief Utility macros for the dichotomia library.
 */
#pragma once

/**
 * @def DICHOTOMIA_ASSUME
 * @brief Compiler-specific hint for optimization based on conditions.
 */
#if defined(__cpp_assume) // C++23 standard feature test macro
  #define DICHOTOMIA_ASSUME(cond) [[assume(cond)]]
#elif defined(__clang__)
  #define DICHOTOMIA_ASSUME(cond) __builtin_assume(cond)
#elif defined(_MSC_VER)
  #define DICHOTOMIA_ASSUME(cond) __assume(cond)
#elif defined(__GNUC__)
  #define DICHOTOMIA_ASSUME(cond) do { if (!(cond)) __builtin_unreachable(); } while(false)
#else
  #define DICHOTOMIA_ASSUME(cond) (void)sizeof(cond)
#endif