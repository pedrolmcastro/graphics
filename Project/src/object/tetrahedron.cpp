#include <array>
#include <functional>

#include "math.hpp"
#include "color.hpp"
#include "render/vertex.hpp"
#include "object/transform.hpp"
#include "object/tetrahedron.hpp"


namespace object {
    class Tetrahedron::Drawer final {
    public:
        static auto get(render::Program const& program) noexcept -> Drawer& {
            static auto instance = Drawer{program};
            return instance;
        }


        auto draw(Transform const& transform) const noexcept -> void {
            program.get().uniform("u_Transform", object::transform(transform));

            for (auto i = 0; i < 4; ++i) {
                program.get().uniform("u_Color", COLORS[i]);
                vertex.draw(1, i);
            }
        }


    private:
        Drawer(render::Program const& program) noexcept : program{program} {
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

        Drawer(Drawer const&) = delete;


        render::Vertex vertex;
        std::reference_wrapper<render::Program const> program; // Caution with dangling reference

        std::array<color::Color, 4> const COLORS = {
            color::RED,
            color::GREEN,
            color::BLUE,
            color::YELLOW,
        };
    };


    auto Tetrahedron::draw(render::Program const& program) const noexcept -> void {
        Drawer::get(program).draw(transform);
    }
}
