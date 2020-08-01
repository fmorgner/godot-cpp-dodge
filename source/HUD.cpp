#include "HUD.hpp"

#include <Button.hpp>
#include <Godot.hpp>
#include <Label.hpp>
#include <SceneTree.hpp>
#include <SceneTreeTimer.hpp>
#include <String.hpp>
#include <Timer.hpp>

namespace dodgetc
{

  auto HUD::_register_methods() -> void
  {
    godot::register_method("show_message", &HUD::show_message);
    godot::register_method("show_game_over", &HUD::show_game_over);
    godot::register_method("update_score", &HUD::update_score);
    godot::register_method("_on_StartButton_pressed", &HUD::_on_StartButton_pressed);
    godot::register_method("_on_MessageTimer_timeout", &HUD::_on_MessageTimer_timeout);
    godot::register_method("_show_start_message", &HUD::_show_start_message);
    godot::register_method("_show_start_button", &HUD::_show_start_button);
    godot::register_signal<HUD>("start_game");
  }

  auto HUD::_init() -> void
  {
  }

  auto HUD::show_message(godot::String text) -> void
  {
    auto message = get_typed_node<godot::Label>("Message");
    message->set_text(std::move(text));
    message->show();

    get_typed_node<godot::Timer>("MessageTimer")->start();
  }

  auto HUD::show_game_over() -> void
  {
    show_message("Game Over");

    auto message_timer = get_typed_node<godot::Timer>("MessageTimer");
    message_timer->connect("timeout", this, "_show_start_message");
  }

  auto HUD::update_score(int score) -> void
  {
    get_typed_node<godot::Label>("ScoreLabel")->set_text(godot::String::num_int64(score));
  }

  auto HUD::_on_StartButton_pressed() -> void
  {
    get_typed_node<godot::Button>("StartButton")->hide();
    emit_signal("start_game");
  }

  auto HUD::_on_MessageTimer_timeout() -> void
  {
    get_typed_node<godot::Label>("Message")->hide();
  }

  auto HUD::_show_start_message() -> void
  {
    auto message_timer = get_typed_node<godot::Timer>("MessageTimer");
    message_timer->disconnect("timeout", this, "_show_start_message");

    auto message = get_typed_node<godot::Label>("Message");
    message->set_text("Dodge the Creeps!");
    message->show();

    auto timer = get_tree()->create_timer(1);
    timer->connect("timeout", this, "_show_start_button");
  }

  auto HUD::_show_start_button() -> void
  {
    get_typed_node<godot::Button>("StartButton")->show();
  }

}  // namespace dodgetc