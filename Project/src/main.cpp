#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>

#include "boid.hpp"
#include "hashgrid.hpp"
#include "math.hpp"
#include "color.hpp"
#include "object.hpp"
#include "render.hpp"
#include "windows.hpp"

auto random_nd() -> math::f32 {
    return (random() % 100) / 50.0 - 1.0;
}

auto random_pos() -> math::vec3 {
    return { random_nd(), random_nd(), random_nd() };
}

auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};

    render::init();
    window.onresize(render::viewport);

    auto program = render::Program{
        render::Shader{GL_VERTEX_SHADER, std::filesystem::path{"shaders/vertex.glsl"}},
        render::Shader{GL_FRAGMENT_SHADER, std::filesystem::path{"shaders/fragment.glsl"}}
    };

    auto boids = std::vector<Boid>();
    std::generate_n(std::back_inserter(boids), 10,
                    [](){return Boid(random_pos(), {random_nd(), random_nd(), 0.0});});

    window.run([&, program](windows::Timestep step) {
        render::clear(color::BLACK);

        auto grid = HashGrid<Boid*>({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1});

        for (auto& boid : boids) {
            grid.insert(boid.position(), &boid);
        }

        auto nearby = std::vector<std::pair<math::vec3, Boid*>>();
        for (auto& boid : boids) {
            nearby.clear();
            grid.query(boid.position(), 0.3, std::back_inserter(nearby));
            boid.update(step);
        }

        for (auto& boid : boids) {
            boid.draw(program);
        }
    });
}
