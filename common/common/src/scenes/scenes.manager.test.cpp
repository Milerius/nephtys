//
// Created by sztergbaum roman on 2019-04-28.
//

#include <memory>
#include <doctest.h>
#include <nephtys/scenes/scenes.manager.hpp>
#include <nephtys/timer/timestep.hpp>

TEST_CASE ("scene_manager")
{
    struct GameScene : public nephtys::scenes::scene
    {
        void update([[maybe_unused]] nephtys::st::delta_time deltaTime) override
        {

        }
    };
    nephtys::timer::time_step ts;
    nephtys::scenes::manager sm{ts};

            SUBCASE("regular way") {
        sm.add_scene<GameScene, "game_scene"_hs>();
        sm.current_scene<"game_scene"_hs>();
        sm.update();
    }

            SUBCASE("sugar way") {
        sm.add_scene<GameScene, "game_scene"_hs, true>();
        sm.update(); //! Update the current scene
    }

            SUBCASE("get_registry") {
        sm.add_scene<GameScene, "game_scene"_hs, true>();
        auto &registry = sm.get_registry();
                CHECK_NE(nullptr, std::addressof(registry));

        const auto &c_registry = const_cast<const nephtys::scenes::manager &>(sm).get_registry();
                CHECK_NE(nullptr, std::addressof(c_registry));

    }
}