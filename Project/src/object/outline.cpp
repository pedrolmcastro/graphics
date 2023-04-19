
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/outline.hpp"
#include "object/transform.hpp"


namespace object::outline {
    Drawer::Drawer(render::Program const& program) : program{program} {
        vertex.attribute(program.location("a_Position"), {
            { - 0.1f, - 0.1f, + 0.0f }, // 0
            { - 0.1f, + 0.1f, + 0.0f }, // 1
            { + 0.1f, - 0.1f, + 0.0f }, // 2
            { + 0.1f, + 0.1f, + 0.0f }, // 3
        });

        vertex.indices(std::initializer_list<math::uvec2>{
            { 0, 2 }, // Bottom
            { 2, 3 }, // Right
            { 3, 1 }, // Top
            { 1, 0 }, // Left
        });
    }

    auto Drawer::get(render::Program const& program) -> Drawer& {
        static auto instance = Drawer{program};
        return instance;
    }


    auto Drawer::draw(Transform const& transform) const -> void {
        program.get().uniform("u_Transform", object::transform(transform));
        program.get().uniform("u_Color", color);
        vertex.lines(4);
    }
}
