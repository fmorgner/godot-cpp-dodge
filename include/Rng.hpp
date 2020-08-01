#ifndef DODGE_THE_CREEPS_RNG_HPP
#define DODGE_THE_CREEPS_RNG_HPP

#include <cstdint>

namespace dodgetc
{
  auto random_int(std::int64_t lower_bound, std::int64_t upper_bound) -> std::int64_t;

  auto random_int() -> std::int64_t;

  auto random_range(float lower_bound, float upper_bound) -> float;
}  // namespace dodgetc

#endif