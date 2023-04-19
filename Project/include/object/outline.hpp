#pragma once


#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    namespace outline {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get(render::Program const& program) -> Drawer&;

            auto draw(Transform const& transform) const -> void;


        private:
            Drawer(render::Program const& program);
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {4, 4};
            color::Color color = color::WHITE;
            std::reference_wrapper<render::Program const> program;
        };
    }

    using Outline = Shape<outline::Drawer>;
}
