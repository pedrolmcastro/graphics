#pragma once


#include "scene/concept.hpp"
#include "object/outline.hpp"
#include "windows/window.hpp"
#include "object/octahedron.hpp"


namespace scene {
    class Translate final {
    public:
        auto start(windows::Window& window) noexcept -> void;

        [[nodiscard]] auto update(windows::Window& window, windows::Timestep step) noexcept -> bool;


    private:
        object::Octahedron translatable = {{ .translation = {- 0.5f, 0.0f, 0.0f} }};
        object::Outline target = {{ .scale = 1.5f, .translation = {0.5f, 0.0f, 0.0f} }};
    };


    static_assert(Scene<Translate>);
}
