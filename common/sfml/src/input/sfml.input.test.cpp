//
// Created by sztergbaum roman on 2019-04-21.
//

#include <doctest.h>
#include <entt/signal/dispatcher.hpp>
#include <entt/entity/registry.hpp>
#include <nephtys/graphics/sfml.graphics.hpp>
#include <nephtys/input/sfml.input.hpp>

namespace nephtys::sfml
{
    TEST_CASE ("sfml input constructor")
    {
      entt::registry<> entity_registry;
      nephtys::window::win_cfg cfg;
      nephtys::sfml::graphics graphical_system{cfg, entity_registry};
          REQUIRE_NE(std::addressof(graphical_system.get_win()), nullptr);
      entt::dispatcher dispatcher;
      nephtys::sfml::input input_system{graphical_system.get_win(), dispatcher};
      input_system.update();
    }
}