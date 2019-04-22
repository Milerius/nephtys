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
        bool operator==(const config &rhs_config) const noexcept
        {
            return window == rhs_config.window;
        }

        /**
         *
         * @param rhs_config the config that you want to compare.
         * @return `true` if the configurations are different, `false` otherwise.
         */
        bool operator!=(const config &rhs_config) const noexcept
        {
            return !(rhs_config == *this);
        }

        window::win_cfg window; //!< window data information
    };


    inline constexpr auto window_json_field = "window";
    inline constexpr auto window_size_json_field = "size";
    inline constexpr auto window_title_json_field = "title";
    inline constexpr auto window_height_json_field = "height";
    inline constexpr auto window_width_json_field = "width";
    inline constexpr auto window_fullscreen_json_field = "fullscreen";

    inline void from_json(const nlohmann::json &json_data, config &game_cfg)
    {
        game_cfg.window.title = json_data.at(window_json_field).at(window_title_json_field).get<std::string>();
        game_cfg.window.height = st::height{
                json_data.at(window_json_field).at(window_size_json_field).at(
                        window_height_json_field).get<std::uint32_t>()};
        game_cfg.window.width = st::width{
                json_data.at(window_json_field).at(window_size_json_field).at(
                        window_width_json_field).get<std::uint32_t>()};
        game_cfg.window.is_fullscreen = json_data.at(window_json_field).at(window_fullscreen_json_field).get<bool>();
    }

    inline void to_json(nlohmann::json &json_data, const config &game_cfg)
    {
        json_data[window_json_field] = nlohmann::json::object();
        json_data[window_json_field][window_size_json_field] = nlohmann::json::object();
        json_data[window_json_field][window_size_json_field][window_height_json_field] = game_cfg.window.height.value();
        json_data[window_json_field][window_size_json_field][window_width_json_field] = game_cfg.window.width.value();
        json_data[window_json_field][window_title_json_field] = game_cfg.window.title;
        json_data[window_json_field][window_fullscreen_json_field] = game_cfg.window.is_fullscreen;
    }
}

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <nephtys/client/config/config.test.hpp>

#endif