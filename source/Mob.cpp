#include "Mob.hpp"

#include "Rng.hpp"

#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>
#include <Input.hpp>
#include <SpriteFrames.hpp>
#include <Viewport.hpp>

#include <algorithm>
#include <cassert>

namespace dodgetc
{

  namespace
  {
    auto constexpr default_minimum_speed{150};
    auto constexpr default_maximum_speed{250};
  }  // namespace

  auto Mob::_register_methods() -> void
  {
    godot::register_method("_ready", &Mob::_ready);
    godot::register_method("_on_VisibilityNotifier2D_screen_exited", &Mob::_on_screen_exited);

    godot::register_property("minimum_speed", &Mob::minimum_speed, default_minimum_speed);
    godot::register_property("maximum_speed", &Mob::maximum_speed, default_maximum_speed);
  }

  auto Mob::_init() -> void
  {
  }

  auto Mob::_ready() -> void
  {
    auto animated_sprite = get_typed_node<godot::AnimatedSprite>("AnimatedSprite");
    auto mob_types = animated_sprite->get_sprite_frames()->get_animation_names();
    animated_sprite->set_animation(mob_types[random_int(0, mob_types.size())]);
  }

  auto Mob::_on_screen_exited() -> void
  {
    queue_free();
  }

}  // namespace dodgetc