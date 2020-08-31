#ifndef DODGE_THE_CREEPS_MAIN_HPP
#define DODGE_THE_CREEPS_MAIN_HPP

#include "Coin.hpp"
#include "TypedNodeCastMixin.hpp"

#include <CanvasLayer.hpp>
#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <Ref.hpp>
#include <Timer.hpp>
#include <Vector2.hpp>

namespace dodgetc
{

  struct Main
      : godot::Node
      , TypedNodeCastMixin<Main>
  {
    static auto _register_methods() -> void;

    auto _init() -> void;
    auto _ready() -> void;

  private:
    GODOT_CLASS(Main, godot::Node);

    auto new_game() -> void;
    auto spawn_coin() -> void;
    auto increase_score(int increment) -> void;

    auto on_player_hit() -> void;
    auto on_player_collected(Coin * coin) -> void;
    auto on_coin_timer_timed_out() -> void;
    auto on_mob_timer_timed_out() -> void;
    auto on_score_timer_timed_out() -> void;
    auto on_start_timer_timed_out() -> void;

    godot::CanvasLayer * coin_layer{};
    godot::CanvasLayer * mob_layer{};

    godot::Ref<godot::PackedScene> coin{};
    godot::Ref<godot::PackedScene> mob{};
    int live_coin_limit{};

    godot::Timer * coin_timer{};

    int score{};
    godot::Vector2 viewport_size{};
  };

}  // namespace dodgetc

#endif