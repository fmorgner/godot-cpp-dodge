#include "Player.hpp"

#include <AnimatedSprite.hpp>
#include <CollisionPolygon2D.hpp>
#include <Input.hpp>
#include <Viewport.hpp>

#include <algorithm>
#include <iostream>

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

    godot::register_property("speed", &Player::speed, default_speed);

    godot::register_signal<Player>("hit");
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

    active_collision_polygon = collision_polygons[0];

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
  }

  auto Player::start(godot::Vector2 position) -> void
  {
    set_position(position);
    sprite->set_animation("up");
    sprite->set_frame(0);
    sprite->set_flip_h(false);
    sprite->set_flip_v(false);
    active_collision_polygon->set_disabled(true);
    active_collision_polygon = collision_polygons[0];
    active_collision_polygon->set_disabled(false);

    show();
  }

  auto Player::on_body_entered(godot::PhysicsBody2D * body) -> void
  {
    hide();
    emit_signal("hit");
    active_collision_polygon->set_deferred("disabled", false);
  }

  auto Player::on_frame_changed() -> void
  {
    auto frame_collision_polygon = collision_polygons[sprite->get_frame() + ((sprite->get_animation() == "up") ? 0 : 2)];
    std::cout << "new collision shape will be: " << frame_collision_polygon << '\n';
    active_collision_polygon->set_disabled(true);
    active_collision_polygon = frame_collision_polygon;
    active_collision_polygon->set_disabled(false);
  }

}  // namespace dodgetc