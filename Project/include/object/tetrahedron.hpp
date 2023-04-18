#pragma once


#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"


namespace object {
    namespace tetrahedron {
        // Singleton for the tetrahedron vertex arrays
        class Drawer final {
        public:
            static auto get(render::Program const& program) noexcept -> Drawer&;


            [[nodiscard]] constexpr auto sides() const noexcept -> std::size_t {
                return COLORS.size();
            }


            // This function assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
            auto draw(Transform const& transform) const -> void;


        private:
            Drawer(render::Program const& program) noexcept;
            Drawer(Drawer const&) = delete;


            render::Vertex vertex;
            std::reference_wrapper<render::Program const> program;

            std::array<color::Color, 4> const COLORS = {
                color::RED,
                color::GREEN,
                color::BLUE,
                color::YELLOW,
            };
        };
    }


    using Tetrahedron = Shape<tetrahedron::Drawer>;
}
