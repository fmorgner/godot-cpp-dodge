#include "Coin.hpp"

#include <CollisionShape2D.hpp>
#include <Shape2D.hpp>

namespace dodgetc
{

  auto Coin::_register_methods() -> void
  {
  }

  auto Coin::_init() -> void
  {
  }

  auto Coin::get_radius() const -> int
  {
    auto collision_shape = get_typed_node<godot::CollisionShape2D>("CollisionShape2D");
    auto radius = collision_shape->get_shape()->get("radius");
    return static_cast<int>(radius);
  }

}  // namespace dodgetc