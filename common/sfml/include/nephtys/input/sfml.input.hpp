//
// Created by sztergbaum roman on 2019-04-21.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace nephtys::sfml
{
    class input
    {
    public:
        explicit input(sf::RenderWindow &win) noexcept;

    private:
        [[maybe_unused]] sf::RenderWindow &win_;
    };
}
