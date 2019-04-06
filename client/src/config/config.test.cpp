//
// Created by milerius on 05/04/19.
//

#include <doctest.h>
#include <nephtys/config/config.hpp>

namespace nephtys::client
{
    TEST_CASE ("get game config from json")
    {
      auto json_game_cfg = R"({"window":{"size":{"height":1200,"width":800},"title":"nephtys"}})"_json;
      config game_cfg;
      CHECK_NOTHROW(from_json(json_game_cfg, game_cfg));
      CHECK_EQ(game_cfg.window.title, "nephtys");
      CHECK_EQ(game_cfg.window.height.value(), 1200u);
      CHECK_EQ(game_cfg.window.width.value(), 800u);
    }
}