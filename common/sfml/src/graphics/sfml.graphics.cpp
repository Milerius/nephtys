//
// Created by sztergbaum roman on 2019-04-20.
//

#include <loguru.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/graphics/sfml.graphics.hpp>

namespace nephtys::sfml
{
    graphics::graphics(window::win_cfg &win_cfg) noexcept :
            win_cfg_(win_cfg),
            win_{sf::VideoMode(win_cfg.width.value(), win_cfg.height.value()), win_cfg_.title}
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }

    const sf::RenderWindow &graphics::get_win() const noexcept
    {
        return win_;
    }

    sf::RenderWindow &graphics::get_win() noexcept
    {
        return win_;
    }
}