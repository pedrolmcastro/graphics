#include <utility>
#include <functional>

#include "color.hpp"
#include "object/cube.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"


namespace object::cube {
    Drawer::Drawer() {
        vertex.attribute(render::Program::location("a_Position"), {
            { - 0.1f, - 0.1f, - 0.1f }, // 0
            { - 0.1f, - 0.1f, + 0.1f }, // 1
            { - 0.1f, + 0.1f, - 0.1f }, // 2
            { - 0.1f, + 0.1f, + 0.1f }, // 3
            { + 0.1f, - 0.1f, - 0.1f }, // 4
            { + 0.1f, - 0.1f, + 0.1f }, // 5
            { + 0.1f, + 0.1f, - 0.1f }, // 6
            { + 0.1f, + 0.1f, + 0.1f }, // 7
        });

        vertex.indices(std::initializer_list<math::uvec3>{
            // Front
            { 0, 4, 6 },
            { 6, 2, 0 },

            // Back
            { 5, 1, 3 },
            { 3, 7, 5 },

            // Right
            { 4, 5, 7 },
            { 7, 6, 4 },

            // Left
            { 1, 0, 2 },
            { 2, 3, 1 },

            // Top
            { 2, 6, 7 },
            { 7, 3, 2 },

            // Bottom
            { 1, 5, 4 },
            { 4, 0, 1 },
        });
    }

    auto Drawer::get() -> Drawer& {
        static auto instance = Drawer{};
        return instance;
    }


    auto Drawer::sides() noexcept -> std::size_t {
        return get().colors.size();
    }

    auto Drawer::draw(Transform const& transform) -> void {
        render::Program::uniform("u_Transform", object::transform(transform));

        for (auto i = 0UL; i < sides(); ++i) {
            render::Program::uniform("u_Color", get().colors[i]);
            get().vertex.triangles(2, i * 2);
        }
    }
}
