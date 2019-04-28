//
// Created by sztergbaum roman on 2019-04-20.
//

#pragma once

#include <utility>
#include <SFML/Graphics/RenderWindow.hpp>
#include <entt/entity/registry.hpp>
#include <meta/sequence/list.hpp>
#include <nephtys/window/win.cfg.hpp>

namespace nephtys::sfml
{
    class graphics
    {
    public:
        explicit graphics(window::win_cfg &win_cfg) noexcept;

        [[nodiscard]] const sf::RenderWindow &get_win() const noexcept;

        sf::RenderWindow &get_win() noexcept;

        void update(entt::registry<> &entity_registry) noexcept;

        template <size_t Layer, typename DrawableType>
        void draw(entt::registry<> &entity_registry) noexcept;

        template <size_t Layer, typename... DrawableType>
        void draw(entt::registry<> &entity_registry, meta::list<DrawableType...>) noexcept;

        template <size_t...Is>
        void draw_each_layers(entt::registry<> &entity_registry, std::index_sequence<Is...>) noexcept;

        void draw_each_layers(entt::registry<> &entity_registry) noexcept;

    private:
        window::win_cfg &win_cfg_;
        sf::RenderWindow win_;
    };
}
