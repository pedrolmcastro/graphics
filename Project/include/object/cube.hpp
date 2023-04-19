#pragma once


#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    namespace cube {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get(render::Program const& program) -> Drawer&;


            [[nodiscard]] constexpr auto sides() const noexcept -> std::size_t {
                return colors.size();
            }

            auto draw(Transform const& transform) const -> void;


        private:
            Drawer(render::Program const& program);
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {8, 12};
            std::reference_wrapper<render::Program const> program;

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
