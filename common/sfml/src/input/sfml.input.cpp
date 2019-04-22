//
// Created by sztergbaum roman on 2019-04-21.
//

#include <SFML/Window/Event.hpp>
#include <loguru.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/input/sfml.input.hpp>
#include <nephtys/event/quit_app.hpp>

namespace nephtys::sfml
{
    input::input(sf::RenderWindow &win, entt::dispatcher &dispatcher) noexcept : win_(win), dispatcher_(dispatcher)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }

    // LCOV_EXCL_START
    void input::update() noexcept
    {
        sf::Event event{};
        while (win_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                dispatcher_.trigger<event::quit_app>();
        }
    }
    // LCOV_EXCL_STOP
}
