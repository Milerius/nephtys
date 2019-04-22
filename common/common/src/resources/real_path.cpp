//
// Created by sztergbaum roman on 2019-04-22.
//

#include <nephtys/resources/real_path.hpp>

namespace nephtys::resources
{
    std::filesystem::path binary_real_path() noexcept
    {
        return details::binary_real_path();
    }

    std::filesystem::path assets_real_path() noexcept
    {
        return details::assets_real_path();
    }
}