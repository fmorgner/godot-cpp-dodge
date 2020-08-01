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
    godot::register_method("on_start_button_pressed", &HUD::on_start_button_pressed);
    godot::register_method("on_message_timer_timed_out", &HUD::on_message_timer_timed_out);
    godot::register_method("show_start_message", &HUD::show_start_message);
    godot::register_method("show_start_button", &HUD::show_start_button);

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
    message_timer->connect("timeout", this, "show_start_message");
  }

  auto HUD::update_score(int score) -> void
  {
    get_typed_node<godot::Label>("ScoreLabel")->set_text(godot::String::num_int64(score));
  }

  auto HUD::on_start_button_pressed() -> void
  {
    get_typed_node<godot::Button>("StartButton")->hide();
    emit_signal("start_game");
  }

  auto HUD::on_message_timer_timed_out() -> void
  {
    get_typed_node<godot::Label>("Message")->hide();
  }

  auto HUD::show_start_message() -> void
  {
    auto message_timer = get_typed_node<godot::Timer>("MessageTimer");
    message_timer->disconnect("timeout", this, "show_start_message");

    auto message = get_typed_node<godot::Label>("Message");
    message->set_text("Dodge the Creeps!");
    message->show();

    auto timer = get_tree()->create_timer(1);
    timer->connect("timeout", this, "show_start_button");
  }

  auto HUD::show_start_button() -> void
  {
    get_typed_node<godot::Button>("StartButton")->show();
  }

}  // namespace dodgetc