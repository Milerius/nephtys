//
// Created by milerius on 05/04/19.
//

#include <nephtys/utils/config.hpp>

namespace nephtys::client
{
    TEST_CASE ("game config from json")
    {
        auto json_game_cfg = R"({"window":{"size":{"height":1200,"width":800},"title":"nephtys", "fullscreen": false}})"_json;
        config game_cfg{};
                CHECK_NOTHROW(from_json(json_game_cfg, game_cfg));
                CHECK_EQ(game_cfg, config{{st::height{1200u}, st::width{800u}, "nephtys", false}});
                CHECK_NE(game_cfg, config{{st::height{1200u}, st::width{800u}, "nephtys_fake", false}});
                CHECK_NE(game_cfg.window, config{{st::height{1200u}, st::width{800u}, "nephtys_fake", false}}.window);
    }

    TEST_CASE ("game config to json")
    {
        auto json_game_cfg = R"({"window":{"size":{"height":1200,"width":800},"title":"nephtys", "fullscreen": false}})"_json;
        config game_cfg{{st::height{1200u}, st::width{800u}, "nephtys", false}};
        nlohmann::json json_data;
                CHECK_NOTHROW(to_json(json_data, game_cfg));
                CHECK_EQ(json_game_cfg, json_data);
    }

    SCENARIO ("loading configuration")
    {
                GIVEN("a configuration doesn't exist in the given path") {
                    AND_WHEN("we load the configuration from a root directory") {
                        THEN("we got a default configuration") {
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
                            REQUIRE_EQ(utils::load_configuration<client::config>("/toto", "nephtys_client.config.json"),
                                       config{});
                            REQUIRE_FALSE(std::filesystem::exists("/toto"));

#else
                    auto res = utils::load_configuration<client::config>(std::filesystem::path("G:\\toto"), "nephtys_client.config.json");
                    REQUIRE_EQ(res, config{});
                    auto path_exist = std::filesystem::exists("G:\\toto");
                    REQUIRE_FALSE(path_exist);
#endif
                }
            }
                    AND_WHEN ("we load the configuration from a non root directory") {
                        THEN("we create a default configuration in the given path and we got a default configuration") {
                            REQUIRE_EQ(
                            utils::load_configuration<client::config>(std::filesystem::current_path() / "my_assets/config",
                                                                      "nephtys_client.config.json"), config{});
                            REQUIRE(std::filesystem::exists(
                            std::filesystem::current_path() / "my_assets/config/nephtys_client.config.json"));
                }
                        AND_THEN("We clear the directory that we create for this test") {
                    std::filesystem::remove_all(std::filesystem::current_path() / "my_assets");
                            REQUIRE_FALSE(std::filesystem::exists(std::filesystem::current_path() / "my_assets"));
                }
            }
        }

                GIVEN ("a configuration exist in the given path") {
            auto path = std::filesystem::current_path() / "assets/config";
                    THEN("we create the configuration and the directories") {
                auto json_game_cfg = R"({"window":{"size":{"height":1200,"width":800},"title":"nephtys", "fullscreen": false}})"_json;
                std::filesystem::create_directories(path);
                        REQUIRE(std::filesystem::exists(path));
                std::ofstream ofs(path / "nephtys_client.config.json");
                        REQUIRE(ofs.is_open());
                ofs << json_game_cfg;
                        REQUIRE(std::filesystem::exists(path / "nephtys_client.config.json"));
            }
                    AND_WHEN("We load the configuration from this fresh directories") {
                        THEN("We got this config") {
                    config game_cfg{{st::height{1200u}, st::width{800u}, "nephtys", false}};
                            REQUIRE_EQ(
                            utils::load_configuration<client::config>(std::move(path), "nephtys_client.config.json"),
                            game_cfg);
                }
                        AND_THEN("We clear the directory that we create for this test") {
                    std::filesystem::remove_all(std::filesystem::current_path() / "assets");
                            REQUIRE_FALSE(std::filesystem::exists(std::filesystem::current_path() / "assets"));
                }
            }
        }
    }
}