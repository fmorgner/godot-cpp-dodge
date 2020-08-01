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

    auto _on_Player_hit() -> void;
    auto _on_MobTimer_timeout() -> void;
    auto _on_ScoreTimer_timeout() -> void;
    auto _on_StartTimer_timeout() -> void;

    auto new_game() -> void;

  private:
    GODOT_CLASS(Main, godot::Node);

    godot::Ref<godot::PackedScene> mob{};
    int score{};
  };

}  // namespace dodgetc

#endif