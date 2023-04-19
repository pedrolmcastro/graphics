#include <array>
#include <utility>
#include <functional>

#include "color.hpp"
#include "object/shape.hpp"
#include "render/vertex.hpp"
#include "render/program.hpp"
#include "object/hexagonal.hpp"


namespace object::hexagonal {
    Drawer::Drawer(render::Program const& program) : program{program} {
        vertex.attribute(program.location("a_Position"), {
            // Top
            { - 0.10f, + 0.1f, + 0.0f }, // 0
            { - 0.05f, + 0.1f, - 0.1f }, // 1
            { - 0.05f, + 0.1f, + 0.1f }, // 2
            { + 0.05f, + 0.1f, - 0.1f }, // 3
            { + 0.05f, + 0.1f, + 0.1f }, // 4
            { + 0.10f, + 0.1f, + 0.0f }, // 5

            // Bottom
            { - 0.10f, - 0.1f, + 0.0f }, // 6
            { - 0.05f, - 0.1f, - 0.1f }, // 7
            { - 0.05f, - 0.1f, + 0.1f }, // 8
            { + 0.05f, - 0.1f, - 0.1f }, // 9
            { + 0.05f, - 0.1f, + 0.1f }, // 10
            { + 0.10f, - 0.1f, + 0.0f }, // 11
        });

        vertex.indices(std::initializer_list<math::uvec3>{
            // Front
            {  7,  9,  3 },
            {  3,  1,  7 },

            // Front right
            {  9, 11,  5 },
            {  5,  3,  9 },

            // Front left
            {  6,  7,  1 },
            {  1,  0,  6 },

            // Back
            { 10,  8,  2 },
            {  2,  4, 10 },

            // Back right
            { 11, 10,  4 },
            {  4,  5, 11 },

            // Back left
            {  8,  6,  0 },
            {  0,  2,  8 },

            // Top
            {  1,  3,  4 },
            {  3,  5,  4 },
            {  4,  2,  1 },
            {  2,  0,  1 },

            // Bottom
            {  8, 10,  9 },
            { 10, 11,  9 },
            {  9,  7,  8 },
            {  7,  6,  8 },
        });
    }

    auto Drawer::get(render::Program const& program) -> Drawer& {
        static auto instance = Drawer{program};
        return instance;
    }


    auto Drawer::draw(Transform const& transform) const -> void {
        program.get().uniform("u_Transform", object::transform(transform));

        auto offset = GLuint{0};
        auto side = 0UL;

        // Sides
        for (side = 0UL; side < sides() - 2UL; ++side) {
            program.get().uniform("u_Color", colors[side]);
            vertex.triangles(2, offset);
            offset += 2;
        }

        // Top and Bottom
        for (; side < sides(); ++side) {
            program.get().uniform("u_Color", colors[side]);
            vertex.triangles(4, offset);
            offset += 4;
        }
    }
}
