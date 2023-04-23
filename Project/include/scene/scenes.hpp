/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include <array>
#include <utility>
#include <variant>

#include "windows/window.hpp"
#include "scene/scale.hpp"
#include "scene/rotate.hpp"
#include "scene/translate.hpp"
#include "scene/boids.hpp"


namespace scene {
    using Variant = std::variant<scene::Scale, scene::Translate, scene::Rotate, scene::Boids>;
    using Array = std::array<Variant, std::variant_size_v<Variant>>;


    class Scenes final {
    public:
        Scenes(windows::Window& window);

        auto update(windows::Timestep step) -> void;


    private:
        Array scenes;
        std::size_t current = 0;
        std::reference_wrapper<windows::Window> window;
    };
}
