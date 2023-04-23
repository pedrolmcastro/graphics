/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include "object/cube.hpp"
#include "scene/concept.hpp"
#include "windows/window.hpp"


namespace scene {
    class Rotate final {
    public:
        auto start(windows::Window& window) noexcept -> void;

        [[nodiscard]] auto update(windows::Window& window, windows::Timestep step) noexcept -> bool;


    private:
        object::Cube target = {{ .rotation = {- 0.5f, 0.5f, 0.0f}, .translation = {0.5f, 0.0f, 0.0f} }};
        object::Cube rotatable = {{ .translation = {- 0.5f, 0.0f, 0.0f} }};
    };


    static_assert(Scene<Rotate>);
}
