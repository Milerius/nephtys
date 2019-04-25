//
// Created by milerius on 25/04/19.
//

#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <meta/sequence/list.hpp>

namespace nephtys::sfml::components
{
    struct sprite
    {
        sf::Sprite drawable;
    };

    struct circle
    {
        sf::CircleShape drawable;
    };

    struct text
    {
        sf::Text drawable;
    };

    using drawable_list = meta::list<sprite, circle, text>;
}