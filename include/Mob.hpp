#ifndef DODGE_THE_CREEPS_MOB_HPP
#define DODGE_THE_CREEPS_MOB_HPP

#include "TypedNodeCastMixin.hpp"

#include <AnimatedSprite.hpp>
#include <CollisionPolygon2D.hpp>
#include <Godot.hpp>
#include <RigidBody2D.hpp>
#include <String.hpp>

#include <array>

namespace dodgetc
{

  struct Mob
      : godot::RigidBody2D
      , TypedNodeCastMixin<Mob>
  {
    auto static _register_methods() -> void;

    auto _init() -> void;
    auto _ready() -> void;

  private:
    GODOT_CLASS(Mob, godot::RigidBody2D)

    auto on_screen_exited() -> void;
    auto on_frame_changed() -> void;

    auto set_collision_polygon(int frame) -> void;

    int minimum_speed{};
    int maximum_speed{};

    godot::String type{};

    godot::AnimatedSprite * sprite{};
    godot::CollisionPolygon2D * active_collision_polygon{};
    std::array<godot::CollisionPolygon2D *, 6> collision_polygons{};
  };

}  // namespace dodgetc

#endif