#include <array>
#include <utility>
#include <variant>

#include "scene/scale.hpp"
#include "scene/rotate.hpp"
#include "scene/scenes.hpp"
#include "windows/window.hpp"
#include "scene/translate.hpp"


namespace scene {
    Scenes::Scenes(windows::Window& window, Array scenes) : scenes{std::move(scenes)}, window{window} {
        std::visit([this](auto& scene) { scene.start(this->window); }, scenes[0]);
    }


    auto Scenes::update(windows::Timestep step) -> void {
        if (current >= scenes.size()) {
            return;
        }

        if (std::visit([this, step](auto& scene) { return scene.update(this->window, step); }, scenes[current])) {
            if (++current < scenes.size()) {
                std::visit([this](auto& scene) { scene.start(this->window); }, scenes[current]);
            }
        }
    }
}
