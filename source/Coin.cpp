#include "Coin.hpp"

#include <CollisionShape2D.hpp>
#include <Godot.hpp>
#include <Shape2D.hpp>
#include <Timer.hpp>

namespace dodgetc
{

  auto Coin::_register_methods() -> void
  {
    godot::register_method("_ready", &Coin::_ready);
    godot::register_method("on_life_timer_timed_out", &Coin::on_life_timer_timed_out);

    godot::register_property("lifetime", &Coin::lifetime, 5);
  }

  auto Coin::_init() -> void
  {
  }

  auto Coin::_ready() -> void
  {
    auto life_timer = get_typed_node<godot::Timer>("LifeTimer");
    life_timer->set_wait_time(lifetime);
    life_timer->start();
  }

  auto Coin::get_radius() const -> int
  {
    auto collision_shape = get_typed_node<godot::CollisionShape2D>("CollisionShape2D");
    auto radius = collision_shape->get_shape()->get("radius");
    return static_cast<int>(radius);
  }

  auto Coin::on_life_timer_timed_out() -> void
  {
    queue_free();
  }

}  // namespace dodgetc