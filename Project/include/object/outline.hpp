#pragma once


#include "color.hpp"
#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    struct Outline final {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer;


        Transform transform;
        color::Color color = color::WHITE;
        color::Color background = color::BLACK;


        auto draw(render::Program const& program) const -> void;
    };
}
