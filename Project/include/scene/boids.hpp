#pragma once

#include "scene/concept.hpp"
#include "windows.hpp"
#include "object/boid.hpp"

namespace scene {
    class Boids final {
    public:
        Boids() noexcept;

        // This type cannot be moved after `start` is called, since it sets up a global handler that
        // references `this`. Since we can't easily know if `start` has been called or not, just
        // avoid moving the type alltogether.
        Boids(Boids&&) = delete;

        auto start(windows::Window& window) noexcept -> void;

        [[nodiscard]] auto update(windows::Window& window, windows::Timestep dt) noexcept -> bool;

    private:
        const float BOID_NEIGHBORHOOD_RADIUS = 0.3;
        const size_t N_INITIAL_BOIDS = 100;

        std::vector<object::Boid> _boids;
    };

    static_assert(Scene<Boids>);
}
