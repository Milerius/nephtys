//
// Created by milerius on 05/04/19.
//

#include <doctest.h>
#include <nephtys/config/config.hpp>

namespace nephtys::client
{
    TEST_CASE ("game config from json")
    {
      auto json_game_cfg = R"({"window":{"size":{"height":1200,"width":800},"title":"nephtys"}})"_json;
      config game_cfg;
      CHECK_NOTHROW(from_json(json_game_cfg, game_cfg));
      CHECK_EQ(game_cfg, config{{st::height{1200u}, st::width{800u}, "nephtys"}});
      CHECK_NE(game_cfg, config{{st::height{1200u}, st::width{800u}, "nephtys_fake"}});
      CHECK_NE(game_cfg.window, config{{st::height{1200u}, st::width{800u}, "nephtys_fake"}}.window);
    }

    TEST_CASE ("game config to json")
    {
      auto json_game_cfg = R"({"window":{"size":{"height":1200,"width":800},"title":"nephtys"}})"_json;
      config game_cfg{{st::height{1200u}, st::width{800u}, "nephtys"}};
      nlohmann::json json_data;
      CHECK_NOTHROW(to_json(json_data, game_cfg));
      CHECK_EQ(json_game_cfg, json_data);
    }
}
