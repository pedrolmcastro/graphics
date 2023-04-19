#include <algorithm>
#include <numeric>
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

auto random_nd() -> float {
    return (random() % 100) / 50.0 - 1.0;
}

auto random_pos() -> math::vec3 {
    return { random_nd(), random_nd(), random_nd() };
}

auto main() -> int {
    auto window = windows::Window{"Window", {800, 800}};

    render::init();
    window.onresize(render::viewport);

    auto program = render::Program{
        render::Shader{GL_VERTEX_SHADER, std::filesystem::path{"shaders/vertex.glsl"}},
        render::Shader{GL_FRAGMENT_SHADER, std::filesystem::path{"shaders/fragment.glsl"}}
    };

    auto boids = std::vector<Boid>();
    std::generate_n(std::back_inserter(boids), 100,
                    [](){return Boid(random_pos(), {random_nd(), random_nd(), 0.0});});

    const float boid_neighborhood_radius = 0.3;

    auto prev_mouse_state = windows::ButtonState::release;

    window.run([&, program](windows::Timestep step) {
        render::clear(color::BLACK);

        auto grid = structures::HashGrid<Boid*>({-1.2, -1.2, -1.2}, {2.4, 2.4, 2.4}, {0.3, 0.3, 0.3});

        for (auto& boid : boids) {
            grid.insert(boid.position(), &boid);
        }

        auto win_cursor = window.cursor();
        // Cursor position in normalized device coordinates
        // NOTE: This only works because the viewport width and height match the window width and height.
        auto cursor = math::vec3{
             2 * win_cursor.x / window.width()  - 1,
            -2 * win_cursor.y / window.height() + 1,
             0,
        };
        
        auto nearby = std::vector<std::pair<math::vec3, Boid*>>();
        for (auto& boid : boids) {
            nearby.clear();
            grid.query(boid.position(), boid_neighborhood_radius, std::back_inserter(nearby));

            boid.cohesion(nearby, 3, step);
            boid.alignment(nearby, 3, step);
            boid.separation(nearby, 3, step);

            auto cursor_dist = math::distance(cursor, boid.position());
            if (cursor_dist <= boid_neighborhood_radius && cursor_dist != 0) {
                boid.steer_towards(boid.position() - cursor, 10, step);
            }

            boid.update(step);
        }

        auto state = window.mouse_button(windows::MouseButton::left);
        // Detect a click transition
        if (prev_mouse_state == windows::ButtonState::release && state == windows::ButtonState::press) {
            boids.push_back(Boid(cursor, {random_nd(), random_nd(), 0}));
        }
        prev_mouse_state = state;

        for (auto& boid : boids) {
            boid.draw(program);
        }
    });
}
