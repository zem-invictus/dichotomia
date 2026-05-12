#pragma once
#include <cstdio>
#include <cstdlib>

#include "macros.h"

namespace zem::math::internal {
[[noreturn]] inline void ReportFailure(const char* condition, const char* file,
                                       int line) noexcept {
  std::fprintf(stderr,
               "[ZEM MATH PANIC] Contract violation: %s\nLocation: %s:%d\n",
               condition, file, line);
  std::abort();
}
}  // namespace zem::math::internal

#ifdef ZEM_MATH_DEBUG

#define ZEM_MATH_EXPECTS(condition)                                         \
  do {                                                                      \
    if (!(condition)) [[unlikely]] {                                        \
      ::zem::math::internal::ReportFailure(#condition, __FILE__, __LINE__); \
    }                                                                       \
  } while (false)
#else
#define ZEM_MATH_EXPECTS(condition) \
  do {                              \
    ZEM_ASSUME(condition);          \
  } while (false)
#endif
