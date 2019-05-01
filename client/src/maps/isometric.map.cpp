//
// Created by sztergbaum roman on 2019-05-01.
//

#include <nephtys/client/maps/isometric.map.hpp>

namespace nephtys::client::maps
{
    void from_json(const nlohmann::json &json_data, tiled_grid &grid_cfg) noexcept
    {
        grid_cfg.width = st::width{json_data.at("width").get<std::uint32_t>()};
        grid_cfg.height = st::height{json_data.at("height").get<std::uint32_t>()};
        grid_cfg.orientation = json_data.at("orientation").get<std::string>();
    }

    void from_json(const nlohmann::json &json_data, tiled_tile &tile_cfg) noexcept
    {
        tile_cfg.id = json_data.at("id").get<int>();
        tile_cfg.image_path = json_data.at("image").get<std::string>();
        tile_cfg.image_height = st::height{json_data.at("imageheight").get<std::uint32_t>()};
        tile_cfg.image_width = st::width{json_data.at("imagewidth").get<std::uint32_t>()};
    }

    void from_json(const nlohmann::json &json_data, tiled_tileset &tileset_cfg) noexcept
    {
        if (json_data.find("grid") != json_data.end()) {
            tileset_cfg.grid = tiled_grid{};
            from_json(json_data.at("grid"), tileset_cfg.grid.value());
        }
        tileset_cfg.columns = json_data.at("columns").get<int>();
        tileset_cfg.margin = json_data.at("margin").get<int>();
        tileset_cfg.name = json_data.at("name").get<std::string>();
        tileset_cfg.spacing = json_data.at("spacing").get<std::size_t>();
        tileset_cfg.tile_count = json_data.at("tilecount").get<std::size_t>();
        tileset_cfg.tiled_version = json_data.at("tiledversion").get<std::string>();
        tileset_cfg.tile_height = st::height{json_data.at("tileheight").get<std::uint32_t>()};
        tileset_cfg.tile_width = st::width{json_data.at("tilewidth").get<std::uint32_t>()};
        tileset_cfg.type = json_data.at("type").get<std::string>();
        tileset_cfg.version = json_data.at("version").get<float>();
        tileset_cfg.tiles = json_data.at("tiles").get<std::vector<tiled_tile>>();
    }

    bool tiled_tileset::operator!=(const tiled_tileset &rhs) const noexcept
    {
        return !(rhs == *this);
    }

    bool tiled_tileset::operator==(const tiled_tileset &rhs) const noexcept
    {
        return grid == rhs.grid &&
               columns == rhs.columns &&
               margin == rhs.margin &&
               name == rhs.name &&
               spacing == rhs.spacing &&
               tile_count == rhs.tile_count &&
               tiled_version == rhs.tiled_version &&
               tile_height == rhs.tile_height &&
               tile_width == rhs.tile_width &&
               type == rhs.type &&
               version == rhs.version &&
               tiles == rhs.tiles;
    }

    bool tiled_grid::operator==(const tiled_grid &rhs) const
    {
        return height == rhs.height &&
               width == rhs.width &&
               orientation == rhs.orientation;
    }

    bool tiled_grid::operator!=(const tiled_grid &rhs) const
    {
        return !(rhs == *this);
    }

    bool tiled_tile::operator==(const tiled_tile &rhs) const noexcept
    {
        return id == rhs.id &&
               image_path == rhs.image_path &&
               image_height == rhs.image_height &&
               image_width == rhs.image_width;
    }

    bool tiled_tile::operator!=(const tiled_tile &rhs) const noexcept
    {
        return !(rhs == *this);
    }
}