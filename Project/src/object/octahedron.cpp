/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/octahedron.hpp"


namespace object::octahedron {
    Drawer::Drawer() {
        vertex.attribute(render::Program::location("a_Position"), {
            { + 0.0f, + 0.1f, + 0.0f }, // 0
            { - 0.1f, + 0.0f, - 0.1f }, // 1
            { - 0.1f, + 0.0f, + 0.1f }, // 2
            { + 0.1f, + 0.0f, - 0.1f }, // 3
            { + 0.1f, + 0.0f, + 0.1f }, // 4
            { + 0.0f, - 0.1f, + 0.0f }, // 5
        });

        vertex.indices(std::initializer_list<math::uvec3>{
            // Top
            { 1, 3, 0 }, // Front
            { 4, 2, 0 }, // Back
            { 3, 4, 0 }, // Right
            { 2, 1, 0 }, // Left

            // Bottom
            { 5, 3, 1 }, // Front
            { 5, 2, 4 }, // Back
            { 5, 4, 3 }, // Right
            { 5, 1, 2 }, // Left
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
            get().vertex.triangles(1, i);
        }
    }
}
