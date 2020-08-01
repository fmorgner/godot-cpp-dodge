#ifndef DODGE_THE_CREEPS_PLAYER_HPP
#define DODGE_THE_CREEPS_PLAYER_HPP

#include "TypedNodeCastMixin.hpp"

#include <Area2D.hpp>
#include <Godot.hpp>
#include <PhysicsBody2D.hpp>
#include <Vector2.hpp>

namespace dodgetc
{

  struct Player
      : godot::Area2D
      , TypedNodeCastMixin<Player>
  {
    auto static _register_methods() -> void;

    auto _init() -> void;
    auto _ready() -> void;
    auto _process(float delta) -> void;

    auto start(godot::Vector2 position) -> void;

  private:
    GODOT_CLASS(Player, godot::Area2D)

    auto on_body_entered(godot::PhysicsBody2D * body) -> void;

    int speed{};
    godot::Vector2 screen_size{};
  };

}  // namespace dodgetc

#endif