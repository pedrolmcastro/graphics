#pragma once


#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"


namespace object {
    namespace outline {
        // Singleton that assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        class Drawer final {
        public:
            static auto get() -> Drawer&;

            static auto draw(Transform const& transform) -> void;


        private:
            Drawer();
            Drawer(Drawer const&) = delete;


            render::Vertex vertex = {4, 4};
            color::Color color = color::WHITE;
        };
    }


    using Outline = Shape<outline::Drawer>;
}
