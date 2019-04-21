//
// Created by sztergbaum roman on 2019-04-20.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <nephtys/window/win.cfg.hpp>

namespace nephtys::sfml
{
    class graphics
    {
    public:
        explicit graphics(window::win_cfg &win_cfg) noexcept;

        const sf::RenderWindow &get_win() const noexcept;

        sf::RenderWindow &get_win() noexcept;


    private:
        [[maybe_unused]] window::win_cfg &win_cfg_;
        [[maybe_unused]] sf::RenderWindow win_;
    };
}
