//
// Created by sztergbaum roman on 2019-04-19.
//

#pragma once

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <loguru.hpp>

namespace nephtys::utils
{
    namespace details
    {
        template<typename TConfig>
        TConfig create_configuration(std::filesystem::path &&config_path,
                                     const std::filesystem::path &full_path) noexcept
        {
            TConfig config_to_export{};
            VLOG_SCOPE_F(loguru::Verbosity_INFO, __FUNCTION__);
            DVLOG_F(loguru::Verbosity_WARNING,
                    "path to nephtys configuration doesn't exist, creating directories + configuration for you");
            std::error_code ec;
            std::filesystem::create_directories(config_path, ec);
            if (ec) {
                VLOG_F(loguru::Verbosity_WARNING, "creating directories failed: %s, returning default configuration",
                       ec.message().c_str());
                return config_to_export;
            }
            std::ofstream ofs(full_path);
            DCHECK_F(ofs.is_open(), "Failed to open: [%s]", full_path.string().c_str());
            nlohmann::json config_json_data;
            config_json_data = config_to_export;
            DVLOG_F(loguru::Verbosity_INFO, "default game config: [%s]", config_json_data.dump().c_str());
            ofs << config_json_data;
            return config_to_export;
        }

        template<typename TConfig>
        TConfig load_configuration(const std::filesystem::path &full_path) noexcept
        {
            TConfig config_to_fill{};
            VLOG_SCOPE_F(loguru::Verbosity_INFO, __FUNCTION__);
            std::ifstream ifs(full_path);
            DCHECK_F(ifs.is_open(), "Failed to open: [%s]", full_path.string().c_str());
            nlohmann::json config_json_data;
            ifs >> config_json_data;
            config_to_fill = config_json_data;
            return config_to_fill;
        }
    }

    template<typename TConfig>
    TConfig load_configuration(std::filesystem::path &&config_path, std::string filename) noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, __FUNCTION__);
        const auto &full_path = config_path / std::move(filename);
        DVLOG_F(loguru::Verbosity_INFO, "path to nephtys configuration -> %s", full_path.string().c_str());
        if (!std::filesystem::exists(config_path)) {
            return details::create_configuration<TConfig>(std::forward<std::filesystem::path>(config_path),
                                                          full_path);
        }
        return details::load_configuration<TConfig>(full_path);
    }
}
