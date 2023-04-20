#include "scene/boids.hpp"
#include "structures/hashgrid.hpp"


namespace scene {

    static auto random_nd() -> float {
        return (random() % 100) / 50.0 - 1.0;
    }

    static auto random_pos() -> math::vec3 {
        return { random_nd(), random_nd(), random_nd() };
    }

    Boids::Boids() noexcept {
        std::generate_n(std::back_inserter(_boids), 100,
                        [](){return object::Boid(random_pos(), {random_nd(), random_nd(), 0.0});});
    }

    auto Boids::start(windows::Window& window) noexcept -> void {
        window.rename("Play with the Boids");
        window.onclick([&](auto& window){
            auto win_cursor = window.cursor();
            auto cursor = math::vec3{
                 2 * win_cursor.x / window.width()  - 1,
                -2 * win_cursor.y / window.height() + 1,
                 0,
            };
            _boids.push_back(object::Boid(cursor, {random_nd(), random_nd(), 0}));
        });
    }

    auto Boids::update(windows::Window& window, windows::Timestep dt) noexcept -> bool {
        auto grid = structures::HashGrid<object::Boid*>({-1.2, -1.2, -1.2}, {2.4, 2.4, 2.4}, {0.3, 0.3, 0.3});

        for (auto& boid : _boids) {
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
        
        auto nearby = std::vector<std::pair<math::vec3, object::Boid*>>();
        for (auto& boid : _boids) {
            nearby.clear();
            grid.query(boid.position(), Boids::BOID_NEIGHBORHOOD_RADIUS, std::back_inserter(nearby));

            boid.cohesion(nearby, 3, dt);
            boid.alignment(nearby, 3, dt);
            boid.separation(nearby, 3, dt);

            auto cursor_dist = math::distance(cursor, boid.position());
            if (cursor_dist <= Boids::BOID_NEIGHBORHOOD_RADIUS && cursor_dist != 0) {
                boid.steer_towards(boid.position() - cursor, 10, dt);
            }

            boid.update(dt);
        }

        for (auto& boid : _boids) {
            boid.draw();
        }

        return false;
    }
}
