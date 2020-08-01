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

    auto _on_StartButton_pressed() -> void;
    auto _on_MessageTimer_timeout() -> void;

  private:
    GODOT_CLASS(HUD, godot::Node);

    auto _show_start_message() -> void;
    auto _show_start_button() -> void;
  };

}  // namespace dodgetc

#endif