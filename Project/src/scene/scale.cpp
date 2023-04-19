#include "scene/scale.hpp"
#include "object/outline.hpp"
#include "windows/window.hpp"
#include "object/hexagonal.hpp"


namespace scene {
    auto Scale::start(windows::Window& window) noexcept -> void {
        window.rename("Resize the object to fit in the target");
    }


    auto Scale::update(windows::Window& window, windows::Timestep step) noexcept -> bool {
        scalable.rotation() += step.count();

        if (window.iskeypressed(GLFW_KEY_UP)) {
            scalable.scale() = std::min(scalable.scale() + step.count() * 3.0f, 5.0f);
        }
        else if (window.iskeypressed(GLFW_KEY_DOWN)) {
            scalable.scale() = std::max(scalable.scale() - step.count() * 3.0f, 0.5f);
        }

        scalable.draw();
        target.draw();

        return scalable.scale() <= 0.6f;
    }
}
