//
// Created by milerius on 06/04/19.
//

#include <string>
#include <unistd.h>
#include <nephtys/resources/details/linux/real_path.hpp>

namespace nephtys::resources::details
{
    std::filesystem::path binary_real_path() noexcept
    {
      return std::filesystem::read_symlink("/proc/" + std::to_string(getpid()) + "/exe");
    }

    std::filesystem::path assets_real_path() noexcept
    {
      return binary_real_path().parent_path().parent_path() / "share/assets/";
    }
}
