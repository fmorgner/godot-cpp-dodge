#ifndef DODGE_THE_CREEPS_HUD_HPP
#define DODGE_THE_CREEPS_HUD_HPP

#include "TypedNodeCastMixin.hpp"

#include <CanvasLayer.hpp>
#include <Godot.hpp>
#include <String.hpp>

namespace dodgetc
{

  struct HUD
      : godot::CanvasLayer
      , TypedNodeCastMixin<HUD>
  {
    static auto _register_methods() -> void;

    auto _init() -> void;

    auto show_message(godot::String text) -> void;
    auto show_game_over() -> void;
    auto update_score(int score) -> void;

  private:
    GODOT_CLASS(HUD, godot::Node);

    auto on_start_button_pressed() -> void;
    auto on_message_timer_timed_out() -> void;

    auto show_start_message() -> void;
    auto show_start_button() -> void;
  };

}  // namespace dodgetc

#endif