//
// Created by milerius on 05/04/19.
//

#include <nephtys/client/config/config.hpp>

inline constexpr const char window_json_field[] = "window";
inline constexpr const char window_size_json_field[] = "size";
inline constexpr const char window_title_json_field[] = "title";
inline constexpr const char window_height_json_field[] = "height";
inline constexpr const char window_width_json_field[] = "width";
inline constexpr const char window_fullscreen_json_field[] = "fullscreen";

namespace nephtys::client
{
    void from_json(const nlohmann::json &json_data, config &game_cfg)
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

    void to_json(nlohmann::json &json_data, const config &game_cfg)
    {
        json_data[window_json_field] = nlohmann::json::object();
        json_data[window_json_field][window_size_json_field] = nlohmann::json::object();
        json_data[window_json_field][window_size_json_field][window_height_json_field] = game_cfg.window.height.value();
        json_data[window_json_field][window_size_json_field][window_width_json_field] = game_cfg.window.width.value();
        json_data[window_json_field][window_title_json_field] = game_cfg.window.title;
        json_data[window_json_field][window_fullscreen_json_field] = game_cfg.window.is_fullscreen;
    }

    bool config::operator!=(const config &rhs_config) const noexcept
    {
        return !(rhs_config == *this);
    }

    bool config::operator==(const config &rhs_config) const noexcept
    {
        return window == rhs_config.window;
    }

    bool win_cfg::operator==(const win_cfg &rhs_win) const noexcept
    {
        return height == rhs_win.height &&
               width == rhs_win.width &&
               title == rhs_win.title &&
               is_fullscreen == rhs_win.is_fullscreen;
    }

    bool win_cfg::operator!=(const win_cfg &rhs_win) const noexcept
    {
        return !(rhs_win == *this);
    }
}