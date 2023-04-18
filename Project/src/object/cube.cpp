#include <utility>
#include <functional>

#include "color.hpp"
#include "object/cube.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"


namespace object::cube {
    Drawer::Drawer(render::Program const& program) : program{program} {
        vertex.attribute(program.location("a_Position"), {
            { - 0.1f, - 0.1f, - 0.1f }, // 0
            { - 0.1f, - 0.1f, + 0.1f }, // 1
            { - 0.1f, + 0.1f, - 0.1f }, // 2
            { - 0.1f, + 0.1f, + 0.1f }, // 3
            { + 0.1f, - 0.1f, - 0.1f }, // 4
            { + 0.1f, - 0.1f, + 0.1f }, // 5
            { + 0.1f, + 0.1f, - 0.1f }, // 6
            { + 0.1f, + 0.1f, + 0.1f }, // 7
        });

        vertex.indices({
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

    auto Drawer::get(render::Program const& program) -> Drawer& {
        static auto instance = Drawer{program};
        return instance;
    }


    auto Drawer::draw(Transform const& transform) const -> void {
        program.get().uniform("u_Transform", object::transform(transform));

        for (auto i = 0UL; i < sides(); ++i) {
            program.get().uniform("u_Color", COLORS[i]);
            vertex.draw(2, i * 2);
        }
    }
}
