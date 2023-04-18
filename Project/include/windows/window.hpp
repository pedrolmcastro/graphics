#pragma once


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <utility>
#include <functional>

#include "math.hpp"


namespace windows {
    // Facade for GLFWwindow
    class Window final {
    public:
        Window(char const* name, math::ivec2 const& size);

        auto run(std::function<void()> const& update) const -> void;


        auto onresize(std::function<void(math::ivec2 const&)> callback) noexcept -> void;


        [[nodiscard]] auto width() const noexcept -> int;
        [[nodiscard]] auto height() const noexcept -> int;

        [[nodiscard]] auto size() const noexcept -> math::ivec2;


    private:
        std::function<void(math::ivec2 const&)> resize;

        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> base = {nullptr, &glfwDestroyWindow};
    };
}
