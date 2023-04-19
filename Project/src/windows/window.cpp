#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>
#include <utility>
#include <functional>
#include <stdexcept>

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

    auto Window::cursor() const noexcept -> math::vec2 {
        double xpos, ypos;
        glfwGetCursorPos(base.get(), &xpos, &ypos);
        return {xpos, ypos};
    }

    auto Window::mouse_button(MouseButton button) const -> ButtonState {
        int state = glfwGetMouseButton(base.get(), static_cast<int>(button));
        switch (state) {
            case GLFW_PRESS: return ButtonState::press;
            case GLFW_RELEASE: return ButtonState::release;
            default: throw std::runtime_error("invalid mouse button state");
        }
    }
}
