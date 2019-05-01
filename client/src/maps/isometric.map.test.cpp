//
// Created by sztergbaum roman on 2019-04-30.
//

#include <doctest.h>
#include <nephtys/client/maps/isometric.map.hpp>

namespace nephtys::client::maps
{
    TEST_CASE ("fill tiled_grid from json")
    {
        tiled_grid wanted_grid{st::height{1}, st::width{1}, "isometric"};
        tiled_grid current_grid{};
        auto json_grid = R"({"height":1,"orientation":"isometric","width":1})"_json;
        from_json(json_grid, current_grid);
                CHECK_EQ(wanted_grid, current_grid);
                CHECK_NE(current_grid, tiled_grid{});
    }

    TEST_CASE ("fill tiled_tile from json")
    {
        auto json_tile = R"({
         "id":0,
         "image":"Assets\/Foundations\/stoneWall_E.png",
         "imageheight":512,
         "imagewidth":256
        })"_json;
        tiled_tile current_tile{};
        tiled_tile wanted_tile{0, R"(Assets/Foundations/stoneWall_E.png)", st::height{512}, st::width{256}};
        from_json(json_tile, current_tile);
                CHECK_EQ(wanted_tile, current_tile);
                CHECK_NE(current_tile, tiled_tile{});
    }

    TEST_CASE ("fill tiled_tileset from json")
    {
        auto json_tileset = R"({ "columns":0,
 "grid":
    {
     "height":1,
     "orientation":"isometric",
     "width":1
    },
 "margin":0,
 "name":"foundations_tiles",
 "spacing":0,
 "tilecount":112,
 "tiledversion":"2019.04.25",
 "tileheight":512,
 "tiles":[
        {
         "id":0,
         "image":"Assets\/Foundations\/stoneWall_E.png",
         "imageheight":512,
         "imagewidth":256
        }],
 "tilewidth":256,
 "type":"tileset",
 "version":1.2
})"_json;

        tiled_tileset current_tileset{};
        tiled_tileset wanted_tileset{tiled_grid{st::height{1}, st::width{1}, "isometric"}, 0, 0, "foundations_tiles", 0,
                                     112, "2019.04.25", st::height{512}, st::width{256}, "tileset", 1.2f,
                                     {{0, R"(Assets/Foundations/stoneWall_E.png)", st::height{512}, st::width{256}}}};
        from_json(json_tileset, current_tileset);
                CHECK_EQ(wanted_tileset, current_tileset);
                CHECK_NE(current_tileset, tiled_tileset{});
    }
}
