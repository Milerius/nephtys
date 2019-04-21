//
// Created by sztergbaum roman on 2019-04-21.
//

#include <loguru.hpp>
#include <nephtys/client/world/world.hpp>
#include <nephtys/utils/pretty_function.hpp>

namespace nephtys::client
{
    world::world() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }
}