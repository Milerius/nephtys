//
// Created by sztergbaum roman on 2019-04-28.
//

#pragma once

#include <loguru.hpp>
#include <nephtys/scenes/scene.hpp>
#include <nephtys/graphics/components/sfml.drawable.hpp>
#include <nephtys/components/layer.hpp>

namespace nephtys::client::scenes
{
    // LCOV_EXCL_START
    class test : public nephtys::scenes::scene
    {
    public:
        test() noexcept
        {
            VLOG_SCOPE_F(loguru::Verbosity_INFO, "%s", pretty_function);
            auto entity = registry_.create();
            auto &component = registry_.assign<nephtys::sfml::components::circle>(entity, 50.f);
            component.drawable.setFillColor(sf::Color(100, 250, 50));
            registry_.assign<nephtys::components::layer<1>>(entity);
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