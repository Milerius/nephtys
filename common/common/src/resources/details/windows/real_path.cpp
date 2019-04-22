//
// Created by milerius on 06/04/19.
//

#include <windows.h>
#include <string>
#include <loguru.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/resources/details/windows/real_path.hpp>

namespace nephtys::client::details
{
    std::filesystem::path binary_real_path() noexcept
    {
      VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
      HMODULE hModule = GetModuleHandleW(NULL);
      DCHECK_F(hModule != nullptr, "unable to get ModuleHandleW: %s", GetLastError());
      WCHAR path[MAX_PATH];
      auto result = GetModuleFileNameW(hModule, path, MAX_PATH);
      DCHECK_F(result != 0, "unable to get executable path: %s", GetLastError());
      return std::filesystem::path(path);
    }

    std::filesystem::path assets_real_path() noexcept
    {
      return binary_real_path();
    }
}
