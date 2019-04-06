//
// Created by milerius on 06/04/19.
//

#include <doctest.h>
#include <nephtys/resources/details/linux/app_image_real_path.hpp>

TEST_CASE ("app_image_real_path not empty")
{
      CHECK_FALSE(nephtys::client::details::app_image_real_path().string().empty());
}

TEST_CASE ("app_image_asset_path not empty")
{
      CHECK_FALSE(nephtys::client::details::app_image_assets_real_path().string().empty());
}