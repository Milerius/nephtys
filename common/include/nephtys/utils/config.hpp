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
    template<typename TConfig>
    TConfig load_configuration(std::filesystem::path &&config_path, std::string filename) noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, __FUNCTION__);
        nlohmann::json config_json_data;
        TConfig loaded_config{};
        const auto &fullpath = config_path / std::move(filename);
        DVLOG_F(loguru::Verbosity_INFO, "path to nephtys configuration -> %s", fullpath.string().c_str());
        if (!std::filesystem::exists(config_path)) {
            DVLOG_F(loguru::Verbosity_WARNING,
                    "path to nephtys configuration doesn't exist, creating directories + configuration for you");
            std::error_code ec;
            std::filesystem::create_directories(config_path, ec);
            if (ec) {
                VLOG_F(loguru::Verbosity_WARNING, "creating directories failed: %s, returning default configuration",
                       ec.message().c_str());
                return loaded_config;
            }
            std::ofstream ofs(fullpath);
            DCHECK_F(ofs.is_open(), "Failed to open: [%s]", fullpath.string().c_str());
            config_json_data = loaded_config;
            DVLOG_F(loguru::Verbosity_INFO, "default game config: [%s]", config_json_data.dump().c_str());
            ofs << config_json_data;
        } else {
            std::ifstream ifs(fullpath);
            DCHECK_F(ifs.is_open(), "Failed to open: [%s]", fullpath.string().c_str());
            ifs >> config_json_data;
            loaded_config = config_json_data;
        }
        return loaded_config;
    }
}
