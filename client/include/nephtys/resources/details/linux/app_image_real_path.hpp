//
// Created by milerius on 06/04/19.
//

#pragma once

#include <filesystem>

namespace nephtys::client::details
{
    std::filesystem::path app_image_real_path() noexcept;
    std::filesystem::path app_image_assets_real_path() noexcept;
}