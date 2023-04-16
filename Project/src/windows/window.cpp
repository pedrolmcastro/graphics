#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <utility>
#include <functional>

#include "windows/state.hpp"
#include "windows/window.hpp"


namespace windows {
    Window::Window(char const* name, std::pair<int, int> size) {
        State::get();
        base.reset(glfwCreateWindow(size.first, size.second, name, nullptr, nullptr));

        if (!base) {
            throw std::runtime_error{"Failed to create GLFW window"};
        }

        glfwMakeContextCurrent(*this);
    }

    auto Window::run(std::function<void()> update) const -> void {
        while (not glfwWindowShouldClose(*this)) {
            glfwPollEvents();
            update();
            glfwSwapBuffers(*this);
        }
    }


    Window::operator GLFWwindow*() const noexcept {
        return base.get();
    }
}
