//
// Created by sztergbaum roman on 2019-04-20.
//

#include <nephtys/graphics/sfml.graphics.hpp>

namespace nephtys::sfml
{
    graphics::graphics(window::win_cfg &win_cfg) noexcept :
            win_cfg_(win_cfg),
            win_{sf::VideoMode(win_cfg.width.value(), win_cfg.height.value()), win_cfg_.title}
    {
    }
}