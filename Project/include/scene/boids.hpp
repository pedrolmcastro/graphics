/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include <vector>
#include <utility>

#include "object/boid.hpp"
#include "scene/concept.hpp"
#include "windows/window.hpp"


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
