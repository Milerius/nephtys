//
// Created by sztergbaum roman on 2019-04-28.
//

#pragma once

#include <entt/entity/registry.hpp>
#include <nephtys/strong_types/delta.time.hpp>

namespace nephtys::scenes
{
    struct scene
    {
        virtual void update(st::delta_time deltaTime) = 0;

        virtual ~scene() noexcept = default;

        [[nodiscard]] const auto &get_registry() const noexcept
        {
            return registry_;
        }

        [[nodiscard]] auto &get_registry() noexcept
        {
            return registry_;
        }

    protected:
        entt::registry<> registry_{};
    };
}
