//
// Created by milerius on 06/04/19.
//

#include <doctest.h>
#include <nephtys/resources/details/linux/real_path.hpp>

TEST_CASE ("binary_real_path not empty")
{
      auto result = nephtys::client::details::binary_real_path().string();
      MESSAGE("binary real path: " + result);
      CHECK_FALSE(nephtys::client::details::binary_real_path().string().empty());
}

TEST_CASE ("asset_path not empty")
{
      auto result = nephtys::client::details::assets_real_path().string();
      MESSAGE("asset path: " + result);
      CHECK_FALSE(result.empty());
}