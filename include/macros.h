#pragma once

#if defined(__cpp_assume) // C++23 standard feature test macro
  #define ZEM_ASSUME(cond) [[assume(cond)]]
#elif defined(__clang__)
  #define ZEM_ASSUME(cond) __builtin_assume(cond)
#elif defined(_MSC_VER)
  #define ZEM_ASSUME(cond) __assume(cond)
#elif defined(__GNUC__)
  #define ZEM_ASSUME(cond) do { if (!(cond)) __builtin_unreachable(); } while(false)
#else
  #define ZEM_ASSUME(cond) (void)sizeof(cond)
#endif