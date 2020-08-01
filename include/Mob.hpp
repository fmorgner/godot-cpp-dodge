#ifndef DODGE_THE_CREEPS_MOB_HPP
#define DODGE_THE_CREEPS_MOB_HPP

#include "TypedNodeCastMixin.hpp"

#include <Godot.hpp>
#include <RigidBody2D.hpp>

namespace dodgetc
{

  struct Mob
      : godot::RigidBody2D
      , TypedNodeCastMixin<Mob>
  {
    auto static _register_methods() -> void;

    auto _init() -> void;
    auto _ready() -> void;

    auto _on_screen_exited() -> void;

  private:
    GODOT_CLASS(Mob, godot::RigidBody2D)

    int minimum_speed{};
    int maximum_speed{};
  };

}  // namespace dodgetc

#endif