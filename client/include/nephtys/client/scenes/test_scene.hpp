//
// Created by sztergbaum roman on 2019-04-28.
//

#pragma once

#include <loguru.hpp>
#include <nephtys/scenes/scene.hpp>

namespace nephtys::client::scenes
{
    // LCOV_EXCL_START
    class test : public nephtys::scenes::scene
    {
    public:
        test() noexcept
        {
            VLOG_SCOPE_F(loguru::Verbosity_INFO, "%s", pretty_function);
        }

        void update([[maybe_unused]] nephtys::st::delta_time deltaTime) final
        {

        }

        ~test() noexcept final
        {
            VLOG_SCOPE_F(loguru::Verbosity_INFO, "%s", pretty_function);
        }
    };
    // LCOV_EXCL_STOP
}