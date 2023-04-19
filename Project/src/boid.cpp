#include "boid.hpp"

static auto wrap(math::f32& coord, math::f32 vel, math::f32 radius) -> void {
    auto margin = 1 + radius;
    if (coord > margin && vel > 0.0) {
        coord = -margin;
    } else if (coord < -margin && vel < 0.0) {
        coord = margin;
    }
}

// source: https://math.stackexchange.com/questions/180418/calculate-rotation-matrix-to-align-vector-a-to-vector-b-in-3d
auto rotation_from_vecs(math::vec3 source, math::vec3 target) -> math::mat3x3 {
    auto v = math::cross(source, target);
    auto s = math::length(v);
    auto c = math::dot(source, target);
    auto skew_symmetric = math::mat3x3{
        {  0.0, -v.z,  v.y },
        {  v.z,  0.0, -v.x },
        { -v.y,  v.x,  0.0 }
    };
    return math::mat3x3{1.0} + skew_symmetric + skew_symmetric * skew_symmetric * (1 - c) / (s * s);
}

// source: https://learnopencv.com/rotation-matrix-to-euler-angles/
auto rotation_matrix_to_euler_angles(math::mat3x3& R) -> math::vec3 {
    math::f32 sy = math::sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]);
    if (sy < 1e-6) {
        return {
            atan2(R[2][1] , R[2][2]),
            atan2(-R[2][0], sy),
            atan2(R[1][0], R[0][0]),
        };
    } else {
        return {
            atan2(-R[1][2], R[1][1]),
            atan2(-R[2][0], sy),
            0,
        };
    }
}

Boid::Boid(math::vec3 position, math::vec3 velocity)
    : _velocity(velocity)
    , _shape(object::Tetrahedron{
          .transform = object::Transform {
              .scale = 0.5,
              .translation = position,
          },
      })
{
    // _shape.transform.rotation = Boid::FRONT;
    // auto rot = rotation_from_vecs(Boid::FRONT, _velocity);
    auto rot = rotation_from_vecs(_velocity, Boid::FRONT);
    _shape.transform.rotation = rotation_matrix_to_euler_angles(rot);
}

[[nodiscard]] auto Boid::position() const noexcept -> math::vec3 {
    return _shape.transform.translation;
}

auto Boid::update(windows::Timestep dt) -> void {
    auto& translation = _shape.transform.translation;
    translation += _velocity * dt.count();

    wrap(translation.x, _velocity.x, 0.2);
    wrap(translation.y, _velocity.y, 0.2);
    wrap(translation.z, _velocity.z, 0.2);

    auto rot = rotation_from_vecs(Boid::FRONT, _velocity);
    _shape.transform.rotation = rotation_matrix_to_euler_angles(rot);

    // _shape.transform.rotation += dt.count();
}

auto Boid::draw(render::Program const& program) const -> void {
    _shape.draw(program);
}
