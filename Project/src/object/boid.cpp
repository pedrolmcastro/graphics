#include <ranges>
#include <vector>
#include <numeric>
#include <utility>

#include "math.hpp"
#include "object/boid.hpp"
#include "windows/window.hpp"
#include "object/tetrahedron.hpp"


namespace views = std::views;


namespace object {
    static auto wrap(float& coord, float vel, float radius) -> void {
        auto margin = 1 + radius;
        if (coord > margin && vel > 0.0) {
            coord = -margin;
        } else if (coord < -margin && vel < 0.0) {
            coord = margin;
        }
    }

    Boid::Boid(math::vec3 position, math::vec3 rotation, math::vec3 velocity)
        : _velocity(velocity)
        , _shape(object::Tetrahedron{
              .transform = object::Transform {
                  .scale = 0.3,
                  .rotation = rotation,
                  .translation = position,
              },
          })
    { }

    [[nodiscard]] auto Boid::position() const noexcept -> math::vec3 {
        return _shape.transform.translation;
    }

    [[nodiscard]] auto Boid::heading() const noexcept -> math::vec3 {
        return math::normalize(_velocity);
    }

    auto Boid::update(windows::Timestep dt) -> void {
        auto& translation = _shape.transform.translation;
        translation += _velocity * dt.count();

        wrap(translation.x, _velocity.x, 0.1 * _shape.transform.scale);
        wrap(translation.y, _velocity.y, 0.1 * _shape.transform.scale);

        _velocity.z = 0;
        translation.z = 0;

        _shape.transform.rotation += dt.count();
    }

    auto Boid::draw() const -> void {
        _shape.draw();
    }

    auto Boid::steer_towards(math::vec3 direction, float weight, windows::Timestep dt) noexcept -> void {
        _velocity += math::normalize(direction) * weight * dt.count();
        if (math::length(_velocity) > Boid::MAX_SPEED) {
            _velocity = math::normalize(_velocity) * Boid::MAX_SPEED;
        }
    }

    auto Boid::cohesion(std::vector<std::pair<math::vec3, Boid*>>& nearby, float weight, windows::Timestep dt) noexcept -> void {
        if (nearby.size() == 0) return;
        auto n = static_cast<float>(nearby.size());
        auto range = nearby | views::transform([](auto neighbor){return neighbor.first;});
        auto avg_pos = std::accumulate(range.begin(), range.end(), math::vec3{0}) / n;
        auto direction = avg_pos - position();
        if (math::length(direction) != 0) {
            steer_towards(direction, weight, dt);
        }
    }

    auto Boid::alignment(std::vector<std::pair<math::vec3, Boid*>>& nearby, float weight, windows::Timestep dt) noexcept -> void {
        if (nearby.size() == 0) return;
        auto range = nearby | views::transform([](auto neighbor){return neighbor.second->heading();});
        auto avg_heading = std::accumulate(range.begin(), range.end(), math::vec3{0}) / static_cast<float>(nearby.size());
        if (math::length(avg_heading) != 0) {
            steer_towards(avg_heading, weight, dt);
        }
    }

    auto Boid::separation(std::vector<std::pair<math::vec3, Boid*>>& nearby, float weight, windows::Timestep dt) noexcept -> void {
        if (nearby.size() == 0) return;
        auto range = nearby | views::transform([&](auto neighbor) {
            auto delta = neighbor.first - position();
            auto dist = math::length(delta);
            if (dist == 0) return math::vec3{0};
            return math::normalize(delta);
        });
        auto avg_dir = std::accumulate(range.begin(), range.end(), math::vec3{0}) / static_cast<float>(nearby.size());
        if (math::length(avg_dir) != 0) {
            steer_towards(-avg_dir, weight, dt);
        }
    }
}
