//
// Created by sztergbaum roman on 2019-04-20.
//

#pragma once

#include <chrono>
#include <nephtys/strong_types/delta.time.hpp>
#include <nephtys/timer/fps.hpp>

namespace nephtys::timer
{
    class time_step
    {
    public:
        time_step() noexcept;

        void start() noexcept;

        void start_frame() noexcept;

        [[nodiscard]] bool is_update_required() const noexcept;

        void perform_update() noexcept;

        [[nodiscard]] st::delta_time get_fixed_delta_time() const noexcept;

    private:
        using clock = std::chrono::steady_clock;
        std::chrono::nanoseconds lag_{0ns};
        std::chrono::nanoseconds fps_{_60fps};
        st::delta_time fixed_delta_time{std::chrono::duration<float, std::ratio<1>>(fps_).count()};
        clock::time_point start_{clock::now()};
    };
}
