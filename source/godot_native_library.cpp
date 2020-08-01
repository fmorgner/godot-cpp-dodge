#include "HUD.hpp"
#include "Main.hpp"
#include "Mob.hpp"
#include "Player.hpp"

#include <GDNative.hpp>

extern "C"
{
  auto GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) -> void
  {
    godot::Godot::gdnative_init(o);
  }

  auto GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) -> void
  {
    godot::Godot::gdnative_terminate(o);
  }

  auto GDN_EXPORT godot_nativescript_init(void * handle) -> void
  {
    godot::Godot::nativescript_init(handle);
    godot::register_class<dodgetc::HUD>();
    godot::register_class<dodgetc::Main>();
    godot::register_class<dodgetc::Mob>();
    godot::register_class<dodgetc::Player>();
  }
}
