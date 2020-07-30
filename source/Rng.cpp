#include "Rng.hpp"

#include <RandomNumberGenerator.hpp>
#include <Ref.hpp>

namespace
{

  static godot::Ref<godot::RandomNumberGenerator> instance{};

  auto get_rng() -> godot::Ref<godot::RandomNumberGenerator>
  {
    if (!instance.is_valid())
    {
      instance = godot::Ref{godot::RandomNumberGenerator::_new()};
    }
    return instance;
  }

}  // namespace

namespace dodgetc
{
  auto random_int(int lower_bound, int upper_bound) -> int
  {
    return get_rng()->randi_range(lower_bound, upper_bound);
  }
}  // namespace dodgetc