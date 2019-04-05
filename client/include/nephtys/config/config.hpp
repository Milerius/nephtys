//
// Created by milerius on 05/04/19.
//

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <nephtys/strong_types/size.hpp>

namespace nephtys::client
{
    struct config
    {
        struct window
        {
            st::height height;
            st::width width;
            std::string title;
        } window;
    };

    void from_json(const nlohmann::json &json_data, config &game_cfg);
}