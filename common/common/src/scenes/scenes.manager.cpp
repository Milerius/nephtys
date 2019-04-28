//
// Created by sztergbaum roman on 2019-04-28.
//

#include <nephtys/scenes/scenes.manager.hpp>

namespace nephtys::scenes
{
    manager::manager(const nephtys::timer::time_step &ts) noexcept : ts_(ts)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, "%s", pretty_function);
    }

    void manager::update() noexcept
    {
        DCHECK_F(current_scene_ != nullptr, "current_scene should be set");
        current_scene_->update(ts_.get_fixed_delta_time());
    }
}