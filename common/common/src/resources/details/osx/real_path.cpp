//
// Created by milerius on 06/04/19.
//

#include <mach-o/dyld.h>    /* _NSGetExecutablePath */
#include <climits>        /* PATH_MAX */
#include <string>
#include <unistd.h>
#include <loguru.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/resources/details/osx/real_path.hpp>

namespace nephtys::client::details
{
    std::filesystem::path binary_real_path() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        std::string dir_name_buffer("", PATH_MAX + 1);
        auto size = static_cast<uint32_t>(dir_name_buffer.max_size());
        [[maybe_unused]] int result = _NSGetExecutablePath(dir_name_buffer.data(), &size);
        DCHECK_F(result == 0, "unable to get executable path, abort");
        return std::filesystem::path(dir_name_buffer);
    }

    std::filesystem::path assets_real_path() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        return binary_real_path().parent_path().parent_path() / "MacOS/assets";
    }
}
