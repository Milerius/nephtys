//
// Created by sztergbaum roman on 2019-04-21.
//

#pragma once

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>
#include <nephtys/utils/config.hpp>
#include <nephtys/client/config/config.hpp>
#include <nephtys/graphics/sfml.graphics.hpp>
#include <nephtys/input/sfml.input.hpp>
#include <nephtys/resources/real_path.hpp>
#include <nephtys/timer/timestep.hpp>
#include <nephtys/strong_types/exit_code.hpp>
#include <nephtys/event/quit_app.hpp>

namespace nephtys::client
{
    class world
    {
    public:
        world() noexcept;

        void receive(const event::quit_app &evt) noexcept;

        void run_once() noexcept;

        st::exit_code run() noexcept;

    private:
        st::exit_code exit_code_{0};
        bool is_running_{false};
        std::filesystem::path assets_path_{nephtys::resources::assets_real_path()};
        config cfg_{nephtys::utils::load_configuration<config>(assets_path_ / "config", "game_config.json")};
        entt::dispatcher dispatcher_;
        entt::registry<> entity_registry_;
        nephtys::timer::time_step timestep_;
        nephtys::sfml::graphics graphical_system_{cfg_.window};
        nephtys::sfml::input input_system_{graphical_system_.get_win(), dispatcher_};
    };
}
