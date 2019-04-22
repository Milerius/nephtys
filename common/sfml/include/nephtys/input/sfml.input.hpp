//
// Created by sztergbaum roman on 2019-04-21.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <entt/signal/dispatcher.hpp>

namespace nephtys::sfml
{
    class input
    {
    public:
        explicit input(sf::RenderWindow &win, entt::dispatcher &dispatcher) noexcept;

        void update() noexcept;

    private:
        [[maybe_unused]] sf::RenderWindow &win_;
        entt::dispatcher &dispatcher_;
    };
}
