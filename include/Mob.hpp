#ifndef DODGE_THE_CREEPS_MOB_HPP
#define DODGE_THE_CREEPS_MOB_HPP

#include <Area2D.hpp>
#include <Godot.hpp>
#include <PhysicsBody2D.hpp>
#include <Vector2.hpp>

namespace dodgetc
{

  struct Mob : godot::Area2D
  {
    auto static _register_methods() -> void;

    auto _ready() -> void;

    auto _on_screen_exited() -> void;

  private:
    GODOT_CLASS(Mob, godot::Area2D)

    int minimum_speed{};
    int maximum_speed{};
  };

}  // namespace dodgetc

#endif