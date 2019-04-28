//
// Created by sztergbaum roman on 2019-04-20.
//

#include <loguru.hpp>
#include <entt/entity/entt_traits.hpp>
#include <nephtys/utils/pretty_function.hpp>
#include <nephtys/components/layer.hpp>
#include <nephtys/graphics/sfml.graphics.hpp>
#include <nephtys/graphics/components/sfml.drawable.hpp>

namespace nephtys::sfml
{
    graphics::graphics(window::win_cfg &win_cfg) noexcept :
        win_cfg_(win_cfg),
        win_{sf::VideoMode(win_cfg.width.value(), win_cfg.height.value()), win_cfg_.title}
    {
      VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }

    const sf::RenderWindow &graphics::get_win() const noexcept
    {
      return win_;
    }

    sf::RenderWindow &graphics::get_win() noexcept
    {
      return win_;
    }

    void graphics::update(entt::registry<> &entity_registry) noexcept
    {
      win_.clear();
        draw_each_layers(entity_registry);
      win_.display();
    }

    // LCOV_EXCL_START
    template <size_t Layer, typename DrawableType>
    void graphics::draw(entt::registry<> &entity_registry) noexcept
    {
        entity_registry.view<DrawableType, nephtys::components::layer<Layer>>().each(
          [this]([[maybe_unused]] auto,
                 auto &&drawable,
                 [[maybe_unused]] auto &&) {
              this->win_.draw(drawable.drawable);
          });
    }
    // LCOV_EXCL_STOP

    template <size_t Layer, typename... DrawableType>
    void graphics::draw(entt::registry<> &entity_registry, meta::list<DrawableType...>) noexcept
    {
        (draw<Layer, DrawableType>(entity_registry), ...);
    }

    template <size_t... Is>
    void graphics::draw_each_layers(entt::registry<> &entity_registry, std::index_sequence<Is...>) noexcept
    {
        (draw<Is>(entity_registry, components::drawable_list{}), ...);
    }

    void graphics::draw_each_layers(entt::registry<> &entity_registry) noexcept
    {
        draw_each_layers(entity_registry, std::make_index_sequence<nephtys::components::max_layer>{});
    }
}