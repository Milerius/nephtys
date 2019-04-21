//
// Created by sztergbaum roman on 2019-04-20.
//

#include <loguru.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/timer/timestep.hpp>

namespace nephtys::timer
{
    void time_step::start() noexcept
    {
        start_ = clock::now();
    }

    void time_step::start_frame() noexcept
    {
        auto deltaTime = clock::now() - start_;
        start_ = clock::now();
        lag_ += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
    }

    bool time_step::is_update_required() const noexcept
    {
        return (lag_ >= fps_);
    }

    void time_step::perform_update() noexcept
    {
        lag_ -= fps_;
    }

    st::delta_time time_step::get_fixed_delta_time() const noexcept
    {
        return fixed_delta_time;
    }

    time_step::time_step() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }
}
