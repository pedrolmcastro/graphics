#pragma once


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
}
