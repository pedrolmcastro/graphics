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

#include "math.hpp"
#include "windows/window.hpp"
#include "object/tetrahedron.hpp"


namespace object {
    class Boid final {
    public:
        Boid(math::vec3 position, math::vec3 rotation, math::vec3 velocity);

        auto update(windows::Timestep dt) -> void;

        auto draw() const -> void;

        [[nodiscard]] auto position() const noexcept -> math::vec3;
        [[nodiscard]] auto heading() const noexcept -> math::vec3;

        auto cohesion(std::vector<std::pair<math::vec3, Boid*>>& nearby, float weight, windows::Timestep dt) noexcept -> void;
        auto alignment(std::vector<std::pair<math::vec3, Boid*>>& nearby, float weight, windows::Timestep dt) noexcept -> void;
        auto separation(std::vector<std::pair<math::vec3, Boid*>>& nearby, float weight, windows::Timestep dt) noexcept -> void;

        auto steer_towards(math::vec3 direction, float weight, windows::Timestep dt) noexcept -> void;

    private:
        const math::vec3 FRONT = {-1, -1, 1};
        const float MAX_SPEED = 1.0;

        math::vec3 _velocity;
        object::Tetrahedron _shape;
    };
}
