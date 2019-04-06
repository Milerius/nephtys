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
        bool operator==(const config &rhs) const;

        bool operator!=(const config &rhs) const;

        struct window
        {
            bool operator==(const window &rhs) const
            {
              return height == rhs.height &&
                     width == rhs.width &&
                     title == rhs.title;
            }

            bool operator!=(const window &rhs) const
            {
              return !(rhs == *this);
            }

            st::height height;
            st::width width;
            std::string title;
        } window;
    };


    void from_json(const nlohmann::json &json_data, config &game_cfg);
    void to_json(nlohmann::json &json_data, const config &game_cfg);
}