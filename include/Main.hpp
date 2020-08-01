#ifndef DODGE_THE_CREEPS_MAIN_HPP
#define DODGE_THE_CREEPS_MAIN_HPP

#include "TypedNodeCastMixin.hpp"

#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <Ref.hpp>

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

    auto on_player_hit() -> void;
    auto on_mob_timer_timed_out() -> void;
    auto on_score_timer_timed_out() -> void;
    auto on_start_timer_timed_out() -> void;

    godot::Ref<godot::PackedScene> mob{};
    int score{};
  };

}  // namespace dodgetc

#endif