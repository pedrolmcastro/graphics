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
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"


namespace object {
    namespace octahedron {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get() -> Drawer&;


            [[nodiscard]] static auto sides() noexcept -> std::size_t;

            static auto draw(Transform const& transform) -> void;


        private:
            Drawer();
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {6, 8};

            std::array<color::Color, 8> colors = {
                // Top
                color::RED,     // Front
                color::MAGENTA, // Back
                color::BLUE,    // Right
                color::CYAN,    // Left

                // Bottom
                color::PURPLE,  // Front
                color::GREEN,   // Back
                color::YELLOW,  // Right
                color::ORANGE,  // Left
            };
        };
    }


    using Octahedron = Shape<octahedron::Drawer>;
}
