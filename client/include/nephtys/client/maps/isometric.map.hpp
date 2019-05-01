//
// Created by sztergbaum roman on 2019-04-29.
//

#pragma once

#include <filesystem>
#include <optional>
#include <vector>
#include <variant>
#include <string>
#include <nlohmann/json.hpp>
#include <nephtys/strong_types/size.hpp>

namespace nephtys::client::maps
{
    struct tiled_grid
    {
        bool operator==(const tiled_grid &rhs) const;

        bool operator!=(const tiled_grid &rhs) const;

        st::height height;
        st::width width;
        std::string orientation;
    };

    void from_json(const nlohmann::json &json_data, tiled_grid &grid_cfg) noexcept;

    struct tiled_tile
    {
        bool operator==(const tiled_tile &rhs) const noexcept;

        bool operator!=(const tiled_tile &rhs) const noexcept;

        int id;
        std::filesystem::path image_path;
        st::height image_height;
        st::width image_width;
    };

    void from_json(const nlohmann::json &json_data, tiled_tile &tile_cfg) noexcept;

    struct tiled_tileset
    {
        std::optional<tiled_grid> grid{std::nullopt};
        int columns;
        int margin;
        std::string name;
        std::size_t spacing;
        std::size_t tile_count;
        std::string tiled_version;
        st::height tile_height;
        st::width tile_width;
        std::string type;

        bool operator==(const tiled_tileset &rhs) const noexcept;

        bool operator!=(const tiled_tileset &rhs) const noexcept;

        float version;
        std::vector<tiled_tile> tiles;
    };

    void from_json(const nlohmann::json &json_data, tiled_tileset &tileset_cfg) noexcept;
}