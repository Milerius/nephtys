//
// Created by sztergbaum roman on 2019-04-21.
//

#pragma once

#include <nephtys/utils/config.hpp>
#include <nephtys/client/config/config.hpp>
#include <nephtys/graphics/sfml.graphics.hpp>
#include <nephtys/input/sfml.input.hpp>
#include <nephtys/timer/timestep.hpp>

namespace nephtys::client
{
    class world
    {
    public:
        world() noexcept;

    private:
        // TODO: Add real path function cross platform to get the asset path
        config cfg_;
        nephtys::timer::time_step timestep_;
        nephtys::sfml::graphics graphical_system_{cfg_.window};
        nephtys::sfml::input input_system_{graphical_system_.get_win()};
    };
}
