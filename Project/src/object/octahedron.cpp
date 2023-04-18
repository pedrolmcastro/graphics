#include <array>
#include <functional>

#include "math.hpp"
#include "color.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"
#include "object/octahedron.hpp"


namespace object {
    class Octahedron::Drawer final {
    public:
        static auto get(render::Program const& program) noexcept -> Drawer& {
            static auto instance = Drawer{program};
            return instance;
        }


        auto draw(Transform const& transform) const noexcept -> void {
            program.get().uniform("u_Transform", object::transform(transform));

            for (auto i = 0; i < 8; ++i) {
                program.get().uniform("u_Color", COLORS[i]);
                vertex.draw(1, i);
            }
        }


    private:
        Drawer(render::Program const& program) noexcept : program{program} {
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

        Drawer(Drawer const&) = delete;


        render::Vertex vertex;
        std::reference_wrapper<render::Program const> program; // Caution with dangling reference

        std::array<color::Color, 8> const COLORS = {
            // Top
            color::RED,     // Front
            color::MAGENTA, // Back
            color::GREEN,   // Right
            color::CYAN,    // Left

            // Bottom
            color::BLUE,    // Front
            color::PURPLE,  // Back
            color::YELLOW,  // Right
            color::ORANGE,  // Left
        };
    };


    auto Octahedron::draw(render::Program const& program) const noexcept -> void {
        Drawer::get(program).draw(transform);
    }
}
