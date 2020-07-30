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
  }
}
