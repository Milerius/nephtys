//
// Created by milerius on 06/04/19.
//

#include <doctest.h>
#include <loguru.hpp>
#include <nephtys/resources/details/linux/real_path.hpp>

TEST_CASE ("binary_real_path not empty")
{
  auto result = nephtys::resources::details::binary_real_path().string();
  DVLOG_F(loguru::Verbosity_INFO, "binary path: %s", result.c_str());
      CHECK_FALSE(result.empty());
}

TEST_CASE ("asset_path not empty")
{
  auto result = nephtys::resources::details::assets_real_path().string();
  DVLOG_F(loguru::Verbosity_INFO, "assets path: %s", result.c_str());
      CHECK_FALSE(result.empty());
}