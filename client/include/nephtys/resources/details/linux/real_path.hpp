//
// Created by milerius on 06/04/19.
//

#pragma once

#include <filesystem>

namespace nephtys::client::details
{
    std::filesystem::path binary_real_path() noexcept;
    std::filesystem::path assets_real_path() noexcept;
}