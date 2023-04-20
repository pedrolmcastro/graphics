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
        Scenes(windows::Window& window, Array scenes);

        auto update(windows::Timestep step) -> void;


    private:
        Array scenes;
        std::size_t current = 0;
        std::reference_wrapper<windows::Window> window;
    };
}
