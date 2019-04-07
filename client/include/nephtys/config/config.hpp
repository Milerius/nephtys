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
     * @brief This is the configuration of the game window/display.
     */
    struct win_cfg
    {
        //! Operator
        bool operator==(const win_cfg &rhs) const; //!< return true if win_cfg are equal
        bool operator!=(const win_cfg &rhs) const; //!< return true if win_cfg are different

        //! win_cfg data members
        st::height height; //!< window height
        st::width width; //!< window width
        std::string title; //!< window title
    };

    /**
     * @struct config
     * @brief This is the game configuration.
     */
    struct config
    {
        //! Operator
        bool operator==(const config &rhs) const; //!< return true if config are equal
        bool operator!=(const config &rhs) const; //!< return true if config are different

        //! config data members
        win_cfg window; //!< window data information
    };

    void from_json(const nlohmann::json &json_data, config &game_cfg);
    void to_json(nlohmann::json &json_data, const config &game_cfg);
}