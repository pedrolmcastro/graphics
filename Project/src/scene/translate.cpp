/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


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
            translatable.translation().y += step.count();
        }
        if (window.iskeypressed(GLFW_KEY_DOWN)) {
            translatable.translation().y -= step.count();
        }
        if (window.iskeypressed(GLFW_KEY_RIGHT)) {
            translatable.translation().x += step.count();
        }
        if (window.iskeypressed(GLFW_KEY_LEFT)) {
            translatable.translation().x -= step.count();
        }

        translatable.draw();
        target.draw();

        return math::distance(translatable.translation(), target.translation()) < 0.02f;
    }
}
