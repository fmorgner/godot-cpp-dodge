#ifndef DODGE_THE_CREEPS_PLAYER_HPP
#define DODGE_THE_CREEPS_PLAYER_HPP

#include "TypedNodeCastMixin.hpp"

#include <AnimatedSprite.hpp>
#include <Area2D.hpp>
#include <CollisionPolygon2D.hpp>
#include <Godot.hpp>
#include <PhysicsBody2D.hpp>
#include <Vector2.hpp>

#include <array>

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

    auto set_collision_polygon(int frame) -> void;

    auto on_body_entered(godot::PhysicsBody2D * body) -> void;
    auto on_frame_changed() -> void;

    int speed{};
    godot::Vector2 screen_size{};
    godot::AnimatedSprite * sprite{};
    godot::CollisionPolygon2D * active_collision_polygon{};
    std::array<godot::CollisionPolygon2D *, 4> collision_polygons{};
  };

}  // namespace dodgetc

#endif