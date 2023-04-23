/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


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


    // Facade for GLFW window
    class Window final {
    public:
        Window(char const* name, math::ivec2 const& size);

        auto run(std::function<void(Timestep)> const& update) const -> void;


        auto onresize(std::function<void(math::ivec2 const&)> callback) noexcept -> void;

        auto onclick(std::function<void(Window&)> callback) noexcept -> void;

        [[nodiscard]] auto iskeypressed(int key) const noexcept -> bool;
        [[nodiscard]] auto ismousepressed(int button) const noexcept -> bool;

        [[nodiscard]] auto cursor() const noexcept -> math::vec2;


        [[nodiscard]] auto width() const noexcept -> int;
        [[nodiscard]] auto height() const noexcept -> int;

        [[nodiscard]] auto size() const noexcept -> math::ivec2;


        auto rename(char const* name) noexcept -> void;


    private:
        std::function<void(math::ivec2 const&)> resize;
        std::function<void(Window&)> click;

        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> base = {nullptr, &glfwDestroyWindow};
    };
}
