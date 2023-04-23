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
    namespace hexagonal {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get() -> Drawer&;


            [[nodiscard]] static auto sides() noexcept -> std::size_t;

            static auto draw(Transform const& transform) -> void;


        private:
            Drawer();
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {12, 20};

            std::array<color::Color, 8> colors = {
                color::RED,     // Front
                color::PURPLE,  // Front right
                color::YELLOW,  // Front left
                color::MAGENTA, // Back
                color::ORANGE,  // Back right
                color::BLUE,    // Back left
                color::GREEN,   // Top
                color::CYAN,    // Bottom
            };
        };
    }


    using Hexagonal = Shape<hexagonal::Drawer>;
}
