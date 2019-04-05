//
// Created by milerius on 05/04/19.
//

#pragma once

#include <st/st.hpp>

namespace nephtys::st
{
    using height = ::st::type<std::uint32_t, struct height_tag, ::st::arithmetic>;
    using width = ::st::type<std::uint32_t, struct height_tag, ::st::arithmetic>;
}