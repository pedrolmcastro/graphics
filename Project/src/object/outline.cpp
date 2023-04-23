/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/outline.hpp"
#include "object/transform.hpp"


namespace object::outline {
    Drawer::Drawer() {
        vertex.attribute(render::Program::location("a_Position"), {
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

    auto Drawer::get() -> Drawer& {
        static auto instance = Drawer{};
        return instance;
    }


    auto Drawer::draw(Transform const& transform) -> void {
        render::Program::uniform("u_Transform", object::transform(transform));
        render::Program::uniform("u_Color", get().color);
        get().vertex.lines(4);
    }
}
