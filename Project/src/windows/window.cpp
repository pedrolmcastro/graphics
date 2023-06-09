/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>
#include <utility>
#include <functional>

#include "math.hpp"
#include "windows/state.hpp"
#include "windows/window.hpp"


namespace windows {
    Window::Window(char const* name, math::ivec2 const& size) {
        State::get();
        base.reset(glfwCreateWindow(size.x, size.y, name, nullptr, nullptr));

        if (!base) {
            throw std::runtime_error{"Failed to create GLFW window"};
        }


        glfwSetWindowUserPointer(base.get(), this);

        glfwSetWindowSizeCallback(base.get(), [](GLFWwindow* window, int width, int height) noexcept {
            auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (self.resize) {
                self.resize({width, height});
            }
        });

        glfwSetMouseButtonCallback(base.get(), [](GLFWwindow* window, int button, int action, int mods) {
            auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && self.click) {
                self.click(self);
            }
        });


        glfwMakeContextCurrent(base.get());
    }


    auto Window::run(std::function<void(Timestep)> const& update) const -> void {
        auto lastframe = std::chrono::steady_clock::now();

        while (not glfwWindowShouldClose(base.get())) {
            glfwPollEvents();

            auto now = std::chrono::steady_clock::now();
            auto step = Timestep{now - lastframe};
            lastframe = now;

            update(step);

            glfwSwapBuffers(base.get());
        }
    }


    auto Window::onresize(std::function<void(math::ivec2 const&)> callback) noexcept -> void {
        resize = std::move(callback);
    }

    auto Window::onclick(std::function<void(Window&)> callback) noexcept -> void {
        click = std::move(callback);
    }

    auto Window::iskeypressed(int key) const noexcept -> bool {
        auto state = glfwGetKey(base.get(), key);
        return state == GLFW_PRESS;
    }

    auto Window::ismousepressed(int button) const noexcept -> bool {
        auto state = glfwGetMouseButton(base.get(), button);
        return state == GLFW_PRESS;
    }

    auto Window::cursor() const noexcept -> math::vec2 {
        double x, y;
        glfwGetCursorPos(base.get(), &x, &y);
        return math::vec2{x, y};
    }


    auto Window::size() const noexcept -> math::ivec2 {
        auto size = math::ivec2{};
        glfwGetWindowSize(base.get(), &size.x, &size.y);
        return size;
    }

    auto Window::width() const noexcept -> int {
        return size().x;
    }

    auto Window::height() const noexcept -> int {
        return size().y;
    }


    auto Window::rename(char const* name) noexcept -> void {
        glfwSetWindowTitle(base.get(), name);
    }
}
