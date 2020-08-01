#include "Main.hpp"

#include "Player.hpp"
#include "Rng.hpp"

#include <Godot.hpp>
#include <PathFollow2D.hpp>
#include <Position2D.hpp>
#include <Ref.hpp>
#include <RigidBody2D.hpp>
#include <Timer.hpp>

#include <cmath>

namespace dodgetc
{

  auto Main::_register_methods() -> void
  {
    godot::register_method("_ready", &Main::_ready);
    godot::register_method("_on_Player_hit", &Main::_on_Player_hit);
    godot::register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
    godot::register_method("_on_ScoreTimer_timeout", &Main::_on_ScoreTimer_timeout);
    godot::register_method("_on_StartTimer_timeout", &Main::_on_StartTimer_timeout);
    godot::register_property("mob", &Main::mob, godot::Ref<godot::PackedScene>{});
  }

  auto Main::_init() -> void
  {
  }

  auto Main::_ready() -> void
  {
    new_game();
  }

  auto Main::_on_Player_hit() -> void
  {
    cast_to<godot::Timer>(get_node("MobTimer"))->stop();
    cast_to<godot::Timer>(get_node("ScoreTimer"))->stop();
  }

  auto Main::_on_MobTimer_timeout() -> void
  {
    auto mob_spawn_location = cast_to<godot::PathFollow2D>(get_node("MobPath/MobSpawnLocation"));
    mob_spawn_location->set_offset(random_int());

    auto mob_instance = cast_to<godot::RigidBody2D>(mob->instance());
    add_child(mob_instance);

    mob_instance->set_position(mob_spawn_location->get_position());
    auto direction = mob_spawn_location->get_rotation() + M_PI_2;
    direction += random_range(-M_PI_4, M_PI_4);
    mob_instance->set_rotation(direction);

    mob_instance->set_linear_velocity(godot::Vector2{random_range(150.f, 250.f), 0}.rotated(direction));
  }

  auto Main::_on_ScoreTimer_timeout() -> void
  {
    ++score;
  }

  auto Main::_on_StartTimer_timeout() -> void
  {
    cast_to<godot::Timer>(get_node("MobTimer"))->start();
    cast_to<godot::Timer>(get_node("MobTimer"))->start();
  }

  auto Main::new_game() -> void
  {
    score = 0;

    auto player = cast_to<Player>(get_node("Player"));
    auto start_position = cast_to<godot::Position2D>(get_node("StartPosition"));
    player->start(start_position->get_position());

    cast_to<godot::Timer>(get_node("StartTimer"))->start();
  }

}  // namespace dodgetc