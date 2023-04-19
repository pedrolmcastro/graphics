#include "math.hpp"
#include "windows/window.hpp"
#include "scene/translate.hpp"
#include "object/hexagonal.hpp"
#include "object/octahedron.hpp"


namespace scene {
    auto Translate::start(windows::Window& window) noexcept -> void {
        window.rename("Move the object the target");
    }


    auto Translate::update(windows::Window& window, windows::Timestep step) noexcept -> bool {
        translatable.rotation() += step.count();

        if (window.iskeypressed(GLFW_KEY_UP)) {
            translatable.translation().y += step.count() * 1.0f;
        }
        if (window.iskeypressed(GLFW_KEY_DOWN)) {
            translatable.translation().y -= step.count() * 1.0f;
        }
        if (window.iskeypressed(GLFW_KEY_RIGHT)) {
            translatable.translation().x += step.count() * 1.0f;
        }
        if (window.iskeypressed(GLFW_KEY_LEFT)) {
            translatable.translation().x -= step.count() * 1.0f;
        }

        translatable.draw();
        target.draw();

        return math::distance(translatable.translation(), target.translation()) < 0.02f;
    }
}
