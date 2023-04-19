#pragma once


#include <array>
#include <utility>
#include <variant>

#include "scene/concept.hpp"
#include "windows/window.hpp"


namespace scene {
    template<Scene ... Types> class Scenes final {
    public:
        Scenes(windows::Window& window) : window{window}, scenes{(Types{} , ...)} {
            std::visit([this](auto& scene) { scene.start(this->window); }, scenes[0]);
        }


        auto update(windows::Timestep step) -> void {
            if (current >= scenes.size()) {
                return;
            }

            if (std::visit([this, step](auto& scene) { return scene.update(this->window, step); }, scenes[current])) {
                if (++current < scenes.size()) {
                    std::visit([this](auto& scene) { scene.start(this->window); }, scenes[current]);
                }
            }
        }


    private:
        std::size_t current = 0;
        std::reference_wrapper<windows::Window> window;
        std::array<std::variant<Types ...>, sizeof...(Types)> scenes;
    };
}
