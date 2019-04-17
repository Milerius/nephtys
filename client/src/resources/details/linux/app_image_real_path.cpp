//
// Created by milerius on 06/04/19.
//

#include <string>
#include <unistd.h>
#include <nephtys/resources/details/linux/app_image_real_path.hpp>

namespace nephtys::client::details
{
    std::filesystem::path app_image_real_path() noexcept
    {
      return std::filesystem::read_symlink("/proc/" + std::to_string(getpid()) + "/exe");
    }

    std::filesystem::path app_image_assets_real_path() noexcept
    {
      return app_image_real_path().parent_path().parent_path() / "share/assets/";
    }
}
