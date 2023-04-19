#pragma once

#include "math.hpp"
#include "object/tetrahedron.hpp"
#include "windows/window.hpp"

class Boid final {
public:
    Boid(math::vec3 position, math::vec3 velocity);

    auto update(windows::Timestep dt) -> void;

    auto draw(render::Program const& program) const -> void;

    [[nodiscard]] auto position() const noexcept -> math::vec3;

private:
    const math::vec3 FRONT = {-1, -1, 1};

    math::vec3 _velocity;
    object::Tetrahedron _shape;
};

