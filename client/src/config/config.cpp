//
// Created by milerius on 05/04/19.
//

#include <nephtys/config/config.hpp>

inline constexpr const char window_json_field[] = "window";
inline constexpr const char window_size_json_field[] = "size";
inline constexpr const char window_title_json_field[] = "title";
inline constexpr const char window_height_json_field[] = "height";
inline constexpr const char window_width_json_field[] = "width";

namespace nephtys::client
{
    void from_json(const nlohmann::json &json_data, config &game_cfg)
    {
      game_cfg.window.title = json_data.at(window_json_field).at(window_title_json_field).get<std::string>();
      game_cfg.window.height = st::height{
          json_data.at(window_json_field).at(window_size_json_field).at(window_height_json_field).get<std::uint32_t>()};
      game_cfg.window.width = st::width{
          json_data.at(window_json_field).at(window_size_json_field).at(window_width_json_field).get<std::uint32_t>()};
    }
}