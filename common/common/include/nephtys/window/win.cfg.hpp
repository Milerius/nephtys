//
// Created by sztergbaum roman on 2019-04-20.
//

#pragma once

#include <string>
#include <nephtys/strong_types/size.hpp>

namespace nephtys::window
{
    /**
     * @struct win_cfg
     * @brief The configuration of the game window contains all
     * the data necessary for its manipulation: **size**, **name**, **full screen** [...]
     */
    struct win_cfg
    {
        /**
         *
         * @param rhs_win the window configuration that you want to compare.
         * @return `true` if the configuration of the windows of the game are identical, `false` otherwise.
         */
        bool operator==(const win_cfg &rhs_win) const noexcept
        {
            return height == rhs_win.height &&
                   width == rhs_win.width &&
                   title == rhs_win.title &&
                   is_fullscreen == rhs_win.is_fullscreen;
        }

        /**
         *
         * @param rhs_win the window configuration that you want to compare
         * @return `true` if the configuration of the windows of the game are different, `false` otherwise.
         */
        bool operator!=(const win_cfg &rhs_win) const noexcept
        {
            return !(rhs_win == *this);
        }

        st::height height{1200}; //!< the height of the game window
        st::width width{800}; //!< the width of the game window
        std::string title{"nephtys client"}; //!< the title of the game window
        bool is_fullscreen{false}; //!< is the window full screen?
    };
}