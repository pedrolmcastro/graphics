#pragma once


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <utility>
#include <functional>


namespace windows {
    // Facade for GLFWwindow
    class Window final {
    public:
        Window(char const* name, std::pair<int, int> size);

        auto run(std::function<void()> update) const -> void;


    private:
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> base = {nullptr, &glfwDestroyWindow};

        [[nodiscard]] operator GLFWwindow*() const noexcept;
    };
}
