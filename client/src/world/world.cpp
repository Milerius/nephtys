//
// Created by sztergbaum roman on 2019-04-21.
//

#include <loguru.hpp>
#include <nephtys/client/world/world.hpp>
#include <nephtys/utils/pretty_function.hpp>

namespace nephtys::client
{
    world::world() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        DVLOG_F(loguru::Verbosity_INFO, "register quit_app event");
        dispatcher_.sink<event::quit_app>().connect<&world::receive>(this);
    }

    void world::receive(const event::quit_app &evt) noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        is_running_ = false;
        exit_code_ = evt.exit_code;
    }

    // LCOV_EXCL_START
    void world::run_once() noexcept
    {
        input_system_.update();
    }

    st::exit_code world::run() noexcept
    {
        is_running_ = true;
        while (is_running_) {
            run_once();
        }
        return exit_code_;
    }
    // LCOV_EXCL_STOP

}