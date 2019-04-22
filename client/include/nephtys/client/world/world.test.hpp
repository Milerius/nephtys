//
// Created by sztergbaum roman on 2019-04-21.
//

namespace nephtys::client
{
    TEST_CASE ("client world constructor")
    {
        world world;
        world.receive(event::quit_app{});
    }
}