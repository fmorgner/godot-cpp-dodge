#include "Player.hpp"

#include <AnimatedSprite.hpp>
#include <CollisionPolygon2D.hpp>
#include <Dictionary.hpp>
#include <Input.hpp>
#include <Viewport.hpp>

#include <algorithm>

namespace dodgetc
{

  namespace
  {
    auto constexpr default_speed{400};
  }

  auto Player::_register_methods() -> void
  {
    godot::register_method("_init", &Player::_init);
    godot::register_method("_ready", &Player::_ready);
    godot::register_method("_process", &Player::_process);
    godot::register_method("on_body_entered", &Player::on_body_entered);
    godot::register_method("start", &Player::start);
    godot::register_method("on_frame_changed", &Player::on_frame_changed);
    godot::register_method("set_collision_polygon", &Player::set_collision_polygon);

    godot::register_property("speed", &Player::speed, default_speed);

    godot::register_signal<Player>("hit", godot::Dictionary{});
  }

  auto Player::_init() -> void
  {
    speed = default_speed;
  }

  auto Player::_ready() -> void
  {
    sprite = get_typed_node<godot::AnimatedSprite>("AnimatedSprite");

    collision_polygons[0] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameUp0");
    collision_polygons[1] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameUp1");
    collision_polygons[2] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameWalk0");
    collision_polygons[3] = get_typed_node<godot::CollisionPolygon2D>("CollisionFrameWalk1");

    screen_size = get_viewport()->get_size();
    hide();
  }

  auto Player::_process(float delta) -> void
  {
    auto velocity = godot::Vector2{};
    auto & input = *godot::Input::get_singleton();

    if (input.is_action_pressed("ui_right"))
    {
      ++velocity.x;
    }
    if (input.is_action_pressed("ui_left"))
    {
      --velocity.x;
    }
    if (input.is_action_pressed("ui_down"))
    {
      ++velocity.y;
    }
    if (input.is_action_pressed("ui_up"))
    {
      --velocity.y;
    }

    if (velocity.length() > 0)
    {
      velocity = velocity.normalized() * speed;
      sprite->play();
    }
    else
    {
      sprite->stop();
    }

    auto position = get_position() + velocity * delta;
    position.x = std::clamp(position.x, .0f, screen_size.x);
    position.y = std::clamp(position.y, .0f, screen_size.y);
    set_position(position);

    if (velocity.x)
    {
      sprite->set_animation("walk");
      sprite->set_flip_v(false);
      sprite->set_flip_h(velocity.x < 0);
    }
    else if (velocity.y)
    {
      sprite->set_animation("up");
      sprite->set_flip_v(velocity.y > 0);
    }

    if (velocity.length())
    {
      call_deferred("set_collision_polygon", sprite->get_frame());
    }
  }

  auto Player::start(godot::Vector2 position) -> void
  {
    set_position(position);
    sprite->set_animation("up");
    sprite->set_frame(0);
    sprite->set_flip_h(false);
    sprite->set_flip_v(false);
    set_collision_polygon(0);
    show();
  }

  auto Player::set_collision_polygon(int frame) -> void
  {
    auto offset = (sprite->get_animation() == "up") ? 0 : 2;
    auto new_collision_polygon = collision_polygons[frame + offset];

    auto constexpr enable_collision_polygon = [](auto polygon) {
      polygon->set_disabled(false);
      polygon->set_visible(true);
    };

    auto constexpr disable_collision_polygon = [](auto polygon) {
      polygon->set_disabled(true);
      polygon->set_visible(false);
    };

    if (!active_collision_polygon)
    {
      active_collision_polygon = new_collision_polygon;
      enable_collision_polygon(active_collision_polygon);
    }
    else if (active_collision_polygon != new_collision_polygon)
    {
      disable_collision_polygon(active_collision_polygon);
      active_collision_polygon = collision_polygons[frame + offset];
      enable_collision_polygon(active_collision_polygon);
    }

    if (sprite->is_flipped_v() != (active_collision_polygon->get_rotation_degrees() != 0.f))
    {
      active_collision_polygon->set_rotation_degrees(sprite->is_flipped_v() ? 180.f : 0.f);
    }
  }

  auto Player::on_body_entered(godot::PhysicsBody2D * body) -> void
  {
    hide();
    emit_signal("hit");
    active_collision_polygon->set_deferred("disabled", false);
  }

  auto Player::on_frame_changed() -> void
  {
    call_deferred("set_collision_polygon", sprite->get_frame());
  }

}  // namespace dodgetc