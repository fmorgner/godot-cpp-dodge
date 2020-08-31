#include "Rng.hpp"

#include <RandomNumberGenerator.hpp>
#include <Ref.hpp>

#include <cstdint>

namespace
{

  static godot::Ref<godot::RandomNumberGenerator> instance{};

  auto get_rng() -> godot::Ref<godot::RandomNumberGenerator>
  {
    if (!instance.is_valid())
    {
      instance = godot::Ref{godot::RandomNumberGenerator::_new()};
      instance->randomize();
    }
    return instance;
  }

}  // namespace

namespace dodgetc
{
  auto random_int(std::int64_t lower_bound, std::int64_t upper_bound) -> std::int64_t
  {
    return get_rng()->randi_range(lower_bound, upper_bound);
  }

  auto random_int() -> std::int64_t
  {
    return get_rng()->randi();
  }

  auto random_range(float lower_bound, float upper_bound) -> float
  {
    return get_rng()->randf_range(lower_bound, upper_bound);
  }
}  // namespace dodgetc