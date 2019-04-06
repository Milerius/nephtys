//
// Created by milerius on 05/04/19.
//

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <nephtys/strong_types/size.hpp>

namespace nephtys::client
{
    struct win_cfg
    {
        //! Operator
        bool operator==(const win_cfg &rhs) const;
        bool operator!=(const win_cfg &rhs) const;

        //! Data
        st::height height;
        st::width width;
        std::string title;
    };

    struct config
    {
        //! Operator
        bool operator==(const config &rhs) const;
        bool operator!=(const config &rhs) const;

        //! Data
        win_cfg window;
    };

    void from_json(const nlohmann::json &json_data, config &game_cfg);
    void to_json(nlohmann::json &json_data, const config &game_cfg);
}