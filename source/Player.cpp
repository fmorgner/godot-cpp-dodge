#include "Player.hpp"

#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>
#include <Input.hpp>
#include <Viewport.hpp>

#include <algorithm>
#include <cassert>

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
    godot::register_method("_on_Player_body_entered", &Player::_on_body_entered);
    godot::register_method("start", &Player::start);

    godot::register_property("speed", &Player::speed, default_speed);

    godot::register_signal<Player>("hit");
  }

  auto Player::_init() -> void
  {
    speed = default_speed;
  }

  auto Player::_ready() -> void
  {
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

    auto animated_sprite = get_typed_node<godot::AnimatedSprite>("AnimatedSprite");
    assert(animated_sprite);

    if (velocity.length() > 0)
    {
      velocity = velocity.normalized() * speed;
      animated_sprite->play();
    }
    else
    {
      animated_sprite->stop();
    }

    auto position = get_position() + velocity * delta;
    position.x = std::clamp(position.x, .0f, screen_size.x);
    position.y = std::clamp(position.y, .0f, screen_size.y);
    set_position(position);

    if (velocity.x)
    {
      animated_sprite->set_animation("walk");
      animated_sprite->set_flip_v(false);
      animated_sprite->set_flip_h(velocity.x < 0);
    }
    else if (velocity.y)
    {
      animated_sprite->set_animation("up");
      animated_sprite->set_flip_v(velocity.y > 0);
    }
  }

  auto Player::start(godot::Vector2 position) -> void
  {
    set_position(position);
    show();
    get_typed_node<godot::CollisionShape2D>("CollisionShape2D")->set_disabled(false);
  }

  auto Player::_on_body_entered(godot::PhysicsBody2D * body) -> void
  {
    hide();
    emit_signal("hit");
    get_typed_node<godot::CollisionShape2D>("CollisionShape2D")->set_deferred("disabled", true);
  }

}  // namespace dodgetc