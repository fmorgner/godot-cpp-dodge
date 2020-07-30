#include "Player.hpp"

#include <AnimatedSprite.hpp>
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
    register_method("_init", &Player::_init);
    register_method("_ready", &Player::_ready);
    register_method("_process", &Player::_process);
    register_property("speed", &Player::speed, default_speed);
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

    auto animated_sprite = cast_to<godot::AnimatedSprite>(get_node("AnimatedSprite"));
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

}  // namespace dodgetc