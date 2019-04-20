//
// Created by milerius on 05/04/19.
//

#pragma once

#include <nlohmann/json.hpp>
#include <nephtys/window/win.cfg.hpp>

namespace nephtys::client
{
    /**
     * @struct config
     * @brief This is the game configuration.
     */
    struct config
    {
        /**
         *
         * @param rhs_config the config that you want to compare.
         * @return `true` if the configurations are equal, `false` otherwise.
         */
        bool operator==(const config &rhs_config) const noexcept;

        /**
         *
         * @param rhs_config the config that you want to compare.
         * @return `true` if the configurations are different, `false` otherwise.
         */
        bool operator!=(const config &rhs_config) const noexcept;

        window::win_cfg window; //!< window data information
    };

    void from_json(const nlohmann::json &json_data, config &game_cfg);

    void to_json(nlohmann::json &json_data, const config &game_cfg);
}