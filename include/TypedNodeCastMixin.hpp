#ifndef DODGE_THE_CREEPS_TYPED_NODE_CAST_MIXIN_HPP
#define DODGE_THE_CREEPS_TYPED_NODE_CAST_MIXIN_HPP

#include <NodePath.hpp>
#include <Object.hpp>

#include <type_traits>
#include <utility>

namespace dodgetc
{

  template<typename CRTP>
  struct TypedNodeCastMixin
  {
    template<typename TargetType>
    auto get_typed_node(godot::NodePath path) -> TargetType *
    {
      static_assert(std::is_base_of_v<godot::Object, CRTP>);

      auto that = static_cast<CRTP *>(this);
      auto node = that->get_node(std::move(path));
      return that->template cast_to<TargetType>(node);
    }
  };

}  // namespace dodgetc

#endif