#pragma once

#include "scene/concept.hpp"
#include "windows.hpp"
#include "object/boid.hpp"

namespace scene {
    class Boids final {
    public:
        Boids() noexcept;

        auto start(windows::Window& window) noexcept -> void;

        [[nodiscard]] auto update(windows::Window& window, windows::Timestep dt) noexcept -> bool;

    private:
        const float BOID_NEIGHBORHOOD_RADIUS = 0.3;

        std::vector<object::Boid> _boids;
    };

    static_assert(Scene<Boids>);
}
