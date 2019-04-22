//
// Created by sztergbaum roman on 2019-04-22.
//

#pragma once

#ifdef _WIN32

#include <nephtys/resources/details/windows/real_path.hpp>

#elif __APPLE__

#include <nephtys/resources/details/osx/real_path.hpp>

#elif __linux__

#include <nephtys/resources/details/linux/real_path.hpp>

#else
#   error "Unknown platform"
#endif

namespace nephtys::resources
{
    std::filesystem::path binary_real_path() noexcept;

    std::filesystem::path assets_real_path() noexcept;
}