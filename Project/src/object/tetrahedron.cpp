#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/tetrahedron.hpp"


namespace object::tetrahedron {
    Drawer::Drawer(render::Program const& program) noexcept : program{program} {
        vertex.attribute(program.location("a_Position"), {
            { - 0.1f, - 0.1f, + 0.1f }, // 0
            { - 0.1f, + 0.1f, - 0.1f }, // 1
            { + 0.1f, - 0.1f, - 0.1f }, // 2
            { + 0.1f, + 0.1f, + 0.1f }, // 3
        });

        vertex.indices({
            { 0, 1, 2 },
            { 0, 1, 3 },
            { 0, 2, 3 },
            { 1, 2, 3 },
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
