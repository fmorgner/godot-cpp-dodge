#ifndef DODGE_THE_CREEPS_COIN_HPP
#define DODGE_THE_CREEPS_COIN_HPP

#include "TypedNodeCastMixin.hpp"

#include <Godot.hpp>
#include <StaticBody2D.hpp>

#include <array>

namespace dodgetc
{

  struct Coin
      : godot::StaticBody2D
      , TypedNodeCastMixin<Coin>
  {
    auto static _register_methods() -> void;

    auto _init() -> void;

    auto get_radius() const -> int;

  private:
    GODOT_CLASS(Coin, godot::StaticBody2D)
  };

}  // namespace dodgetc

#endif