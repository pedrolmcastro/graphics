#include <cmath>
#include <functional>

#include "color.hpp"
#include "render/vertex.hpp"
#include "object/outline.hpp"
#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    class Outline::Drawer final {
    public:
        static auto get(render::Program const& program) -> Drawer& {
            static auto instance = Drawer{program};
            return instance;
        }

        auto draw(Transform const& transform, color::Color const& color, color::Color const& background) const -> void {
            program.get().uniform("u_Transform", object::transform(transform));

            // Outter
            program.get().uniform("u_Color", color);
            vertex.draw(2);

            // Inner
            program.get().uniform("u_Color", background);
            vertex.draw(2, 2);
        }


    private:
        Drawer(render::Program const& program) : program{program} {
            vertex.attribute(program.location("a_Position"), {
                // Outter
                { - 0.100f, - 0.100f, + 0.0f }, // 0
                { - 0.100f, + 0.100f, + 0.0f }, // 1
                { + 0.100f, - 0.100f, + 0.0f }, // 2
                { + 0.100f, + 0.100f, + 0.0f }, // 3

                // Inner
                { - 0.085f, - 0.085f, - 0.01f }, // 4
                { - 0.085f, + 0.085f, - 0.01f }, // 5
                { + 0.085f, - 0.085f, - 0.01f }, // 6
                { + 0.085f, + 0.085f, - 0.01f }, // 7
            });

            vertex.indices({
                // Top
                { 0, 2, 3 },
                { 3, 1, 0 },

                // Inner
                { 4, 6, 7 },
                { 7, 5, 4 },
            });
        }

        Drawer(Drawer const&) = delete;


        render::Vertex vertex = {8, 4};
        std::reference_wrapper<render::Program const> program;
    };


    auto Outline::draw(render::Program const& program) const -> void {
        Drawer::get(program).draw(transform, color, background);
    }
}
