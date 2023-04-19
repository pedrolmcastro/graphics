#pragma once


#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"


namespace object {
    namespace cube {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get() -> Drawer&;


            [[nodiscard]] static auto sides() noexcept -> std::size_t;

            static auto draw(Transform const& transform) -> void;


        private:
            Drawer();
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {8, 12};

            std::array<color::Color, 6> colors = {
                color::RED,     // Front
                color::MAGENTA, // Back
                color::GREEN,   // Right
                color::YELLOW,  // Left
                color::BLUE,    // Top
                color::CYAN,    // Bottom
            };
        };
    }


    using Cube = Shape<cube::Drawer>;
}
