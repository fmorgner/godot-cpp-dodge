#include "Mob.hpp"

#include "Rng.hpp"

#include <AnimatedSprite.hpp>
#include <CollisionPolygon2D.hpp>
#include <SpriteFrames.hpp>

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
    godot::register_method("on_screen_exited", &Mob::on_screen_exited);
    godot::register_method("on_frame_changed", &Mob::on_frame_changed);
    godot::register_method("set_collision_polygon", &Mob::set_collision_polygon);

    godot::register_property("minimum_speed", &Mob::minimum_speed, default_minimum_speed);
    godot::register_property("maximum_speed", &Mob::maximum_speed, default_maximum_speed);
  }

  auto Mob::_init() -> void
  {
    minimum_speed = default_minimum_speed;
    maximum_speed = default_maximum_speed;
  }

  auto Mob::_ready() -> void
  {
    sprite = get_typed_node<godot::AnimatedSprite>("AnimatedSprite");

    collision_polygons[0] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameFly0");
    collision_polygons[1] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameFly1");
    collision_polygons[2] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameSwim0");
    collision_polygons[3] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameSwim1");
    collision_polygons[4] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameWalk0");
    collision_polygons[5] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameWalk1");

    auto mob_types = sprite->get_sprite_frames()->get_animation_names();
    type = mob_types[random_int(0, mob_types.size() - 1)];
    set_collision_polygon(0);
    sprite->set_animation(type);
  }

  auto Mob::set_collision_polygon(int frame) -> void
  {
    auto offset = (type == "fly") ? 0 : (type == "swim") ? 2 : 4;

    if (active_collision_polygon)
    {
      active_collision_polygon->set_disabled(true);
      active_collision_polygon->set_visible(false);
    }

    active_collision_polygon = collision_polygons[frame + offset];
    active_collision_polygon->set_disabled(false);
    active_collision_polygon->set_visible(true);
  }

  auto Mob::on_screen_exited() -> void
  {
    queue_free();
  }

  auto Mob::on_frame_changed() -> void
  {
    call_deferred("set_collision_polygon", sprite->get_frame());
  }

}  // namespace dodgetc