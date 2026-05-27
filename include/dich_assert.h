/**
 * @file dich_assert.h
 * @brief Custom assertion and contract checking for dichotomia.
 */
#pragma once
#include <cstdio>
#include <cstdlib>

#include "macros.h"

namespace dich::internal {
[[noreturn]] inline void ReportFailure(const char* condition, const char* file,
                                       int line) noexcept {
  std::fprintf(stderr,
               "[DICHOTOMIA PANIC] Contract violation: %s\nLocation: %s:%d\n",
               condition, file, line);
  std::abort();
}
}  // namespace dich::internal

#ifdef DICHOTOMIA_DEBUG

#define DICHOTOMIA_EXPECTS(condition)                                       \
  do {                                                                      \
    if (!(condition)) [[unlikely]] {                                        \
      ::dich::internal::ReportFailure(#condition, __FILE__, __LINE__); \
    }                                                                       \
  } while (false)
#else
#define DICHOTOMIA_EXPECTS(condition) \
  do {                                \
    DICHOTOMIA_ASSUME(condition);     \
  } while (false)
#endif
