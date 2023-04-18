#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/octahedron.hpp"


namespace object::octahedron {
    Drawer::Drawer(render::Program const& program) noexcept : program{program} {
        vertex.attribute(program.location("a_Position"), {
            { + 0.0f, + 0.1f, + 0.0f }, // 0
            { - 0.1f, + 0.0f, - 0.1f }, // 1
            { - 0.1f, + 0.0f, + 0.1f }, // 2
            { + 0.1f, + 0.0f, - 0.1f }, // 3
            { + 0.1f, + 0.0f, + 0.1f }, // 4
            { + 0.0f, - 0.1f, + 0.0f }, // 5
        });

        vertex.indices({
            // Top
            {1, 3, 0}, // Front
            {4, 2, 0}, // Back
            {3, 4, 0}, // Right
            {2, 1, 0}, // Left

            // Bottom
            {5, 3, 1}, // Front
            {5, 2, 4}, // Back
            {5, 4, 3}, // Right
            {5, 1, 2}, // Left
        });
    }

    auto Drawer::get(render::Program const& program) noexcept -> Drawer& {
        static auto instance = Drawer{program};
        return instance;
    }


    auto Drawer::draw(Transform const& transform) const -> void {
        program.get().uniform("u_Transform", object::transform(transform));

        for (auto i = 0UL; i < sides(); ++i) {
            program.get().uniform("u_Color", COLORS[i]);
            vertex.draw(1, i);
        }
    }
}
