//
// Created by milerius on 06/04/19.
//

#include <mach-o/dyld.h>    /* _NSGetExecutablePath */
#include <unistd.h>
#include <climits>        /* PATH_MAX */
#include <array>
#include <regex>
#include <string>
#include <loguru.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/resources/details/osx/real_path.hpp>

namespace nephtys::resources::details
{
    static std::string &replace_all_mute(std::string &s,
                                         const std::string from, const std::string &to) noexcept
    {
        if (!from.empty())
            for (std::size_t pos = 0; (pos = s.find(from, pos) + 1); pos += to.size())
                s.replace(--pos, from.size(), to);
        return s;
    }

    static std::string replace_all_copy(std::string s,
                                        const std::string from, const std::string &to) noexcept
    {
        return replace_all_mute(s, from, to);
    }

    std::filesystem::path binary_real_path() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        std::array<char, PATH_MAX + 1> dir_name_buffer;
        auto size = static_cast<uint32_t>(dir_name_buffer.size());
        [[maybe_unused]] int result = _NSGetExecutablePath(dir_name_buffer.data(), &size);
        DCHECK_F(result == 0, "unable to get executable path, abort");
        std::string tmp_path(dir_name_buffer.data());
        auto final_path = replace_all_copy(tmp_path, "./", "");
        return std::filesystem::path(final_path);
    }

    std::filesystem::path assets_real_path() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        return binary_real_path().parent_path().parent_path() / "Resources/assets";
    }
}
