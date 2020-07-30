#ifndef DODGE_THE_CREEPS_PLAYER_HPP
#define DODGE_THE_CREEPS_PLAYER_HPP

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Vector2.hpp>

namespace dodgetc
{

  struct Player : godot::Area2D
  {
    auto static _register_methods() -> void;

    auto _init() -> void;
    auto _ready() -> void;
    auto _process(float delta) -> void;

  private:
    GODOT_CLASS(Player, godot::Area2D)

    int speed{};
    godot::Vector2 screen_size{};
  };

}  // namespace dodgetc

#endif