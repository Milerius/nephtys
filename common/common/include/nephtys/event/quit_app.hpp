//
// Created by sztergbaum roman on 2019-04-22.
//

#pragma once

#include <loguru.hpp>
#include <nephtys/strong_types/exit_code.hpp>

namespace nephtys::event
{
    struct quit_app
    {
        explicit quit_app(st::exit_code exit_code_) noexcept : exit_code(exit_code_)
        {
            DVLOG_F(loguru::Verbosity_INFO, "quit_app event trigger with exit_code: %d", exit_code_.value());
        }

        quit_app() noexcept
        {
            DVLOG_F(loguru::Verbosity_INFO, "quit_app event trigger with default exit_code: 0");
        }

        st::exit_code exit_code{0}; // NOLINT(misc-non-private-member-variables-in-classes)
    };
}
