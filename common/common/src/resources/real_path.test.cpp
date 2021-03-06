//
// Created by sztergbaum roman on 2019-04-22.
//

#include <doctest.h>
#include <loguru.hpp>
#include <nephtys/resources/real_path.hpp>

TEST_CASE ("binary_real_path not empty")
{
    auto result = nephtys::resources::binary_real_path().string();
    DVLOG_F(loguru::Verbosity_INFO, "binary path: %s", result.c_str());
            CHECK_FALSE(nephtys::resources::details::binary_real_path().string().empty());
}

TEST_CASE ("asset_path not empty")
{
    auto result = nephtys::resources::assets_real_path().string();
    DVLOG_F(loguru::Verbosity_INFO, "assets path: %s", result.c_str());
            CHECK_FALSE(result.empty());
}