//
// Created by sztergbaum roman on 2019-04-28.
//

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <loguru.hpp>
#include <entt/core/hashed_string.hpp>
#include <nephtys/timer/timestep.hpp>
#include <nephtys/scenes/scene.hpp>
#include <nephtys/utils/pretty_function.hpp>

namespace nephtys::scenes
{
    class manager
    {
    public:
        explicit manager(const nephtys::timer::time_step &ts) noexcept;

        template<class Scene, entt::hashed_string::hash_type SceneNameHash, bool isCurrentScene = false>
        void add_scene() noexcept
        {
            VLOG_SCOPE_F(loguru::Verbosity_INFO, "%s", pretty_function);
            scenes_registry_.emplace(SceneNameHash, []() { return std::make_unique<Scene>(); });
            if constexpr (isCurrentScene) {
                current_scene<SceneNameHash>();
            }
        }

        void update() noexcept;

        template<entt::hashed_string::hash_type SceneNameHash>
        void current_scene() noexcept
        {
            VLOG_SCOPE_F(loguru::Verbosity_INFO, "%s", pretty_function);
            DVLOG_F(loguru::Verbosity_INFO, "adding scene: %llu", SceneNameHash);
            current_scene_ = scenes_registry_.at(SceneNameHash)();
        }

        [[nodiscard]] const auto &get_registry() const noexcept
        {
            DCHECK_F(current_scene_ != nullptr, "current_scene should be set");
            return current_scene_->get_registry();
        }

        [[nodiscard]] auto &get_registry() noexcept
        {
            DCHECK_F(current_scene_ != nullptr, "current_scene should be set");
            return current_scene_->get_registry();
        }

    private:
        const nephtys::timer::time_step &ts_;
        std::unordered_map<entt::hashed_string::hash_type, std::function<std::unique_ptr<scene>()>> scenes_registry_;
        std::unique_ptr<scene> current_scene_{nullptr};
    };
}
