//
// Created by sztergbaum roman on 2019-04-20.
//

#include <memory>
#include <doctest.h>
#include <nephtys/graphics/sfml.graphics.hpp>

namespace nephtys::sfml
{
    TEST_CASE ("sfml graphics constructor")
    {
      entt::registry<> entity_registry;
      nephtys::window::win_cfg cfg;
      nephtys::sfml::graphics graphical_system{cfg, entity_registry};
          REQUIRE_NE(std::addressof(graphical_system.get_win()), nullptr);
      const nephtys::sfml::graphics cst_graphical_system{cfg, entity_registry};
          REQUIRE_NE(std::addressof(cst_graphical_system.get_win()), nullptr);
      graphical_system.update();
    }
}