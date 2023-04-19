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
