/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#include <numbers>

#include "math.hpp"
#include "object/cube.hpp"
#include "scene/rotate.hpp"
#include "windows/window.hpp"


#include <iostream>


namespace scene {
    auto Rotate::start(windows::Window& window) noexcept -> void {
        window.rename("Rotate the object to match the other");
    }


    auto Rotate::update(windows::Window& window, windows::Timestep step) noexcept -> bool {
        auto const pi = static_cast<float>(std::numbers::pi);

        if (window.iskeypressed(GLFW_KEY_UP)) {
            rotatable.rotation().x = std::clamp(rotatable.rotation().x + step.count(), - pi, pi);
        }
        if (window.iskeypressed(GLFW_KEY_DOWN)) {
            rotatable.rotation().x = std::clamp(rotatable.rotation().x - step.count(), - pi, pi);
        }
        if (window.iskeypressed(GLFW_KEY_RIGHT)) {
            rotatable.rotation().y = std::clamp(rotatable.rotation().y - step.count(), - pi, pi);
        }
        if (window.iskeypressed(GLFW_KEY_LEFT)) {
            rotatable.rotation().y = std::clamp(rotatable.rotation().y + step.count(), - pi, pi);
        }

        rotatable.draw();
        target.draw();

        return math::all(math::lessThan(math::abs(rotatable.rotation() - target.rotation()), math::vec3{0.05f}));
    }
}
