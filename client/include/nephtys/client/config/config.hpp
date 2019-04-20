//
// Created by milerius on 05/04/19.
//

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <nephtys/strong_types/size.hpp>

namespace nephtys::client
{
    /**
     * @struct win_cfg
     * @brief The configuration of the game window contains all
     * the data necessary for its manipulation: **size**, **name**, **full screen** [...]
     */
    struct win_cfg
    {
        /**
         *
         * @param rhs_win the window configuration that you want to compare.
         * @return `true` if the configuration of the windows of the game are identical, `false` otherwise.
         */
        bool operator==(const win_cfg &rhs_win) const noexcept;

        /**
         *
         * @param rhs_win the window configuration that you want to compare
         * @return `true` if the configuration of the windows of the game are different, `false` otherwise.
         */
        bool operator!=(const win_cfg &rhs_win) const noexcept;

        st::height height{1200}; //!< the height of the game window
        st::width width{800}; //!< the width of the game window
        std::string title{"nephtys client"}; //!< the title of the game window
        bool is_fullscreen{false}; //!< is the window full screen?
    };

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

        win_cfg window; //!< window data information
    };

    void from_json(const nlohmann::json &json_data, config &game_cfg);

    void to_json(nlohmann::json &json_data, const config &game_cfg);
}