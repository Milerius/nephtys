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
        world() noexcept
        {
          VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
          DVLOG_F(loguru::Verbosity_INFO, "register quit_app event");
          dispatcher_.sink<event::quit_app>().connect<&world::receive>(this);
        }

        void receive(const event::quit_app &evt) noexcept
        {
          VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
          is_running_ = false;
          exit_code_ = evt.exit_code;
        }

        // LCOV_EXCL_START
        inline void run_once() noexcept
        {
          timestep_.start_frame();
          input_system_.update();
          while (timestep_.is_update_required()) {
            graphical_system_.updareboote();
            timestep_.perform_update();
          }
        }

        inline st::exit_code run() noexcept
        {
          is_running_ = true;
          timestep_.start();
          while (is_running_) {
            run_once();
          }
          return exit_code_;
        }
        // LCOV_EXCL_STOP


    private:
        st::exit_code exit_code_{0};
        bool is_running_{false};
        std::filesystem::path assets_path_{nephtys::resources::assets_real_path()};
        config cfg_{nephtys::utils::load_configuration<config>(assets_path_ / "config", "game_config.json")};
        entt::dispatcher dispatcher_;
        entt::registry<> entity_registry_{};
        nephtys::timer::time_step timestep_;
        nephtys::sfml::graphics graphical_system_{cfg_.window, entity_registry_};
        nephtys::sfml::input input_system_{graphical_system_.get_win(), dispatcher_};
    };
}

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <nephtys/client/world/world.test.hpp>

#endif