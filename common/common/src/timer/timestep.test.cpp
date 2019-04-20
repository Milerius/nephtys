//
// Created by sztergbaum roman on 2019-04-20.
//

#include <doctest.h>
#include <nephtys/timer/timestep.hpp>

TEST_CASE ("all timestep functions are callable")
{
    nephtys::timer::time_step ts;
    ts.start();
    ts.start_frame();
            REQUIRE_FALSE(ts.is_update_required());
    ts.perform_update();
            REQUIRE_GT(ts.get_fixed_delta_time(), nephtys::st::delta_time{0.f});
}