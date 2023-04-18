#include <array>
#include <functional>

#include "math.hpp"
#include "color.hpp"
#include "object/cube.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"


namespace object {
    class Cube::Drawer final {
    public:
        static auto get(render::Program const& program) noexcept -> Drawer& {
            static auto instance = Drawer{program};
            return instance;
        }


        auto draw(Transform const& transform) const noexcept -> void {
            program.get().uniform("u_Transform", object::transform(transform));

            for (auto i = 0; i < 6; ++i) {
                program.get().uniform("u_Color", COLORS[i]);
                vertex.draw(2, i * 2);
            }
        }


    private:
        Drawer(render::Program const& program) noexcept : program{program} {
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
                {0, 4, 6},
                {6, 2, 0},

                // Back
                {5, 1, 3},
                {3, 7, 5},

                // Right
                {4, 5, 7},
                {7, 6, 4},

                // Left
                {1, 0, 2},
                {2, 3, 1},

                // Top
                {2, 6, 7},
                {7, 3, 2},

                // Bottom
                {1, 5, 4},
                {4, 0, 1},
            });
        }

        Drawer(Drawer const&) = delete;


        render::Vertex vertex;
        std::reference_wrapper<render::Program const> program; // Caution with dangling reference

        std::array<color::Color, 6> const COLORS = {
            color::RED,     // Front
            color::MAGENTA, // Back
            color::GREEN,   // Right
            color::YELLOW,  // Left
            color::BLUE,    // Top
            color::CYAN,    // Bottom
        };
    };


    auto Cube::draw(render::Program const& program) const noexcept -> void {
        Drawer::get(program).draw(transform);
    }
}
