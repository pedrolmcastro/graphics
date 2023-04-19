#pragma once


#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"


namespace object {
    namespace tetrahedron {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get() -> Drawer&;


            [[nodiscard]] static auto sides() noexcept -> std::size_t;

            static auto draw(Transform const& transform) -> void;


        private:
            Drawer();
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {4, 4};

            std::array<color::Color, 4> colors = {
                color::RED,
                color::GREEN,
                color::BLUE,
                color::YELLOW,
            };
        };
    }


    using Tetrahedron = Shape<tetrahedron::Drawer>;
}
