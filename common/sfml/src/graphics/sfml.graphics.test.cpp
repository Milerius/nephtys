//
// Created by sztergbaum roman on 2019-04-20.
//

#include <doctest.h>
#include <nephtys/graphics/sfml.graphics.hpp>

namespace nephtys::sfml
{
    TEST_CASE ("sfml graphics constructor")
    {
        nephtys::window::win_cfg cfg;
        nephtys::sfml::graphics graphical_system{cfg};
    }
}