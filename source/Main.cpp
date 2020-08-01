#include "Main.hpp"

#include "HUD.hpp"
#include "Player.hpp"
#include "Rng.hpp"

#include <AudioStreamPlayer.hpp>
#include <Godot.hpp>
#include <PathFollow2D.hpp>
#include <Position2D.hpp>
#include <Ref.hpp>
#include <RigidBody2D.hpp>
#include <SceneTree.hpp>
#include <Timer.hpp>

#include <cmath>
#include <iostream>

namespace dodgetc
{

  auto Main::_register_methods() -> void
  {
    godot::register_method("_ready", &Main::_ready);
    godot::register_method("_on_Player_hit", &Main::_on_Player_hit);
    godot::register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
    godot::register_method("_on_ScoreTimer_timeout", &Main::_on_ScoreTimer_timeout);
    godot::register_method("_on_StartTimer_timeout", &Main::_on_StartTimer_timeout);
    godot::register_method("new_game", &Main::new_game);
    godot::register_property("mob", &Main::mob, godot::Ref<godot::PackedScene>{});
  }

  auto Main::_init() -> void
  {
  }

  auto Main::_ready() -> void
  {
  }

  auto Main::_on_Player_hit() -> void
  {
    get_typed_node<godot::Timer>("MobTimer")->stop();
    get_typed_node<godot::Timer>("ScoreTimer")->stop();

    get_typed_node<godot::AudioStreamPlayer>("Music")->stop();
    get_typed_node<godot::AudioStreamPlayer>("DeathSound")->play();

    get_typed_node<HUD>("HUD")->show_game_over();

    get_tree()->call_group("mobs", "queue_free");
  }

  auto Main::_on_MobTimer_timeout() -> void
  {
    auto mob_spawn_location = get_typed_node<godot::PathFollow2D>("MobPath/MobSpawnLocation");
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
    get_typed_node<HUD>("HUD")->update_score(score);
  }

  auto Main::_on_StartTimer_timeout() -> void
  {
    get_typed_node<godot::Timer>("MobTimer")->start();
    get_typed_node<godot::Timer>("ScoreTimer")->start();
  }

  auto Main::new_game() -> void
  {
    score = 0;

    auto player = get_typed_node<Player>("Player");
    auto start_position = get_typed_node<godot::Position2D>("StartPosition");
    player->start(start_position->get_position());

    get_typed_node<godot::Timer>("StartTimer")->start();

    auto hud = get_typed_node<HUD>("HUD");
    hud->update_score(score);
    hud->show_message("Get Ready!");

    get_typed_node<godot::AudioStreamPlayer>("Music")->play();
  }

}  // namespace dodgetc