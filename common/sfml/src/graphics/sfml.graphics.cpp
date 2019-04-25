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
    graphics::graphics(window::win_cfg &win_cfg, entt::registry<> &entity_registry) noexcept :
        win_cfg_(win_cfg),
        entity_registry_(entity_registry),
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

    void graphics::update() noexcept
    {
      win_.clear();
      draw_each_layers();
      win_.display();
    }

    // LCOV_EXCL_START
    template <size_t Layer, typename DrawableType>
    void graphics::draw() noexcept
    {
      entity_registry_.view<DrawableType, nephtys::components::layer<Layer>>().each(
          [this]([[maybe_unused]] entt::registry<>::entity_type entity,
                 const DrawableType &drawable,
                 [[maybe_unused]] const nephtys::components::layer<Layer> &layer) {
              this->win_.draw(drawable.drawable);
          });
    }
    // LCOV_EXCL_STOP

    template <size_t Layer, typename... DrawableType>
    void graphics::draw(meta::list<DrawableType...>) noexcept
    {
      (draw<Layer, DrawableType>(), ...);
    }

    template <size_t... Is>
    void graphics::draw_each_layers(std::index_sequence<Is...>) noexcept
    {
      (draw<Is>(components::drawable_list{}), ...);
    }

    void graphics::draw_each_layers() noexcept
    {
      draw_each_layers(std::make_index_sequence<nephtys::components::max_layer>{});
    }
}