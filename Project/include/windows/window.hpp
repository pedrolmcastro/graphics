#pragma once


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>
#include <utility>
#include <functional>

#include "math.hpp"


namespace windows {
    using Timestep = std::chrono::duration<float>;

    // TODO: Maybe move this enum to a more appropriate namespace
    enum class MouseButton : int {
        left = GLFW_MOUSE_BUTTON_LEFT,
        right = GLFW_MOUSE_BUTTON_RIGHT,
    };

    enum class ButtonState : int {
        press = GLFW_PRESS,
        release = GLFW_RELEASE,
    };

    // Facade for GLFWwindow
    class Window final {
    public:
        Window(char const* name, math::ivec2 const& size);

        auto run(std::function<void(Timestep)> const& update) const -> void;


        auto onresize(std::function<void(math::ivec2 const&)> callback) noexcept -> void;


        [[nodiscard]] auto width() const noexcept -> int;
        [[nodiscard]] auto height() const noexcept -> int;

        [[nodiscard]] auto size() const noexcept -> math::ivec2;

        [[nodiscard]] auto cursor() const noexcept -> math::vec2;
        [[nodiscard]] auto mouse_button(MouseButton button) const -> ButtonState;

    private:
        std::function<void(math::ivec2 const&)> resize;

        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> base = {nullptr, &glfwDestroyWindow};
    };
}
