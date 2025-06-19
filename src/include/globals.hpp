#pragma once

#include <cstdio>

#include <string>

namespace spinarak {
namespace globals {

#define DEBUG_MODE true;
#ifdef DEBUG_MODE
#  define DEBUG(fmt, ...)                                                              \
      do {                                                                             \
          fprintf(stderr, fmt, ##__VA_ARGS__);                                         \
      } while (0)
#else
#  define DEBUG(fmt, ...)                                                              \
      do {                                                                             \
      } while (0)
#endif

constexpr std::string name = "spinarak";

} // namespace globals
} // namespace spinarak
