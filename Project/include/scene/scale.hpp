/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include "scene/concept.hpp"
#include "object/outline.hpp"
#include "windows/window.hpp"
#include "object/hexagonal.hpp"


namespace scene {
    class Scale final {
    public:
        auto start(windows::Window& window) noexcept -> void;

        [[nodiscard]] auto update(windows::Window& window, windows::Timestep step) noexcept -> bool;


    private:
        object::Outline target;
        object::Hexagonal scalable = {{ .scale = 2.0f }};
    };


    static_assert(Scene<Scale>);
}
