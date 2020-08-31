#include "Main.hpp"

#include "Coin.hpp"
#include "HUD.hpp"
#include "Mob.hpp"
#include "Player.hpp"
#include "Rng.hpp"

#include <AudioStreamPlayer.hpp>
#include <Godot.hpp>
#include <Particles2D.hpp>
#include <PathFollow2D.hpp>
#include <Position2D.hpp>
#include <Ref.hpp>
#include <SceneTree.hpp>
#include <Timer.hpp>
#include <Vector2.hpp>
#include <Viewport.hpp>

#include <cmath>
#include <utility>

namespace dodgetc
{

  auto Main::_register_methods() -> void
  {
    godot::register_method("_ready", &Main::_ready);
    godot::register_method("on_player_hit", &Main::on_player_hit);
    godot::register_method("on_player_collected", &Main::on_player_collected);
    godot::register_method("on_coin_timer_timed_out", &Main::on_coin_timer_timed_out);
    godot::register_method("on_mob_timer_timed_out", &Main::on_mob_timer_timed_out);
    godot::register_method("on_score_timer_timed_out", &Main::on_score_timer_timed_out);
    godot::register_method("on_start_timer_timed_out", &Main::on_start_timer_timed_out);
    godot::register_method("new_game", &Main::new_game);

    godot::register_property("coin", &Main::coin, godot::Ref<godot::PackedScene>{});
    godot::register_property("mob", &Main::mob, godot::Ref<godot::PackedScene>{});
    godot::register_property("live_coin_limit", &Main::live_coin_limit, 3);
  }

  auto Main::_init() -> void
  {
  }

  auto Main::_ready() -> void
  {
    coin_timer = get_typed_node<godot::Timer>("CoinTimer");

    viewport_size = get_viewport()->get_size();
  }

  auto Main::on_player_hit() -> void
  {
    get_typed_node<godot::Timer>("MobTimer")->stop();
    get_typed_node<godot::Timer>("ScoreTimer")->stop();
    coin_timer->stop();

    get_typed_node<godot::AudioStreamPlayer>("Music")->stop();
    get_typed_node<godot::AudioStreamPlayer>("DeathSound")->play();

    auto player = get_typed_node<Player>("Player");
    auto death_particles = get_typed_node<godot::Particles2D>("DeathParticles");
    death_particles->set_position(player->get_position());
    death_particles->set_visible(true);
    death_particles->set_emitting(true);
    death_particles->restart();

    get_typed_node<HUD>("HUD")->show_game_over();

    get_tree()->call_group("mobs", "queue_free");
    get_tree()->call_group("coins", "queue_free");
  }

  auto Main::on_player_collected(Coin * coin) -> void
  {
    coin->queue_free();
    increase_score(5);
  }

  auto Main::on_coin_timer_timed_out() -> void
  {
    auto coins = get_tree()->get_nodes_in_group("coins");
    if (coins.size() < 3)
    {
      spawn_coin();
    }
  }

  auto Main::on_mob_timer_timed_out() -> void
  {
    auto mob_spawn_location = get_typed_node<godot::PathFollow2D>("MobPath/MobSpawnLocation");
    mob_spawn_location->set_offset(random_int());

    auto mob_instance = cast_to<Mob>(mob->instance());
    mob_instance->set_position(mob_spawn_location->get_position());
    auto direction = mob_spawn_location->get_rotation() + M_PI_2;
    direction += random_range(-M_PI_4, M_PI_4);
    mob_instance->set_rotation(direction);
    auto minimum_velocity = mob_instance->get("minimum_speed");
    auto maximum_velocity = mob_instance->get("maximum_speed");
    mob_instance->set_linear_velocity(godot::Vector2{random_range(minimum_velocity, maximum_velocity), 0}.rotated(direction));

    add_child(mob_instance);
  }

  auto Main::on_score_timer_timed_out() -> void
  {
    increase_score(1);
  }

  auto Main::on_start_timer_timed_out() -> void
  {
    get_typed_node<godot::Timer>("MobTimer")->start();
    get_typed_node<godot::Timer>("ScoreTimer")->start();
    coin_timer->start();
  }

  auto Main::new_game() -> void
  {
    score = 0;

    auto death_particles = get_typed_node<godot::Particles2D>("DeathParticles");
    death_particles->set_visible(false);

    auto player = get_typed_node<Player>("Player");
    auto start_position = get_typed_node<godot::Position2D>("StartPosition");
    player->start(start_position->get_position());

    get_typed_node<godot::Timer>("StartTimer")->start();

    auto hud = get_typed_node<HUD>("HUD");
    hud->update_score(score);
    hud->show_message("Get Ready!");

    get_typed_node<godot::AudioStreamPlayer>("Music")->play();
  }

  auto Main::spawn_coin() -> void
  {
    auto new_coin = cast_to<Coin>(coin->instance());
    auto radius = new_coin->get_radius();

    auto x_bounds = std::pair{10.f + radius, viewport_size.x - 10 - radius};
    auto y_bounds = std::pair{10.f + radius, viewport_size.y - 10 - radius};

    new_coin->set_position({
        random_range(x_bounds.first, x_bounds.second),
        random_range(y_bounds.first, y_bounds.second),
    });

    add_child(new_coin);
  }

  auto Main::increase_score(int increment) -> void
  {
    score += increment;
    get_typed_node<HUD>("HUD")->update_score(score);
  }

}  // namespace dodgetc