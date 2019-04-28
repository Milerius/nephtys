//
// Created by milerius on 25/04/19.
//

#pragma once

#include <utility>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <meta/sequence/list.hpp>

namespace nephtys::sfml::components
{
    // LCOV_EXCL_START
    struct sprite
    {
        sf::Sprite drawable;
    };

    struct circle
    {
        explicit circle(float radius) noexcept : drawable(radius)
        {
        }

        circle() = default;

        sf::CircleShape drawable;
    };

    struct text
    {
        sf::Text drawable;
    };
    // LCOV_EXCL_STOP

    using drawable_list = meta::list<sprite, circle, text>;
}