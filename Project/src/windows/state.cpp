/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "windows/state.hpp"


namespace windows {
    State::State() {
        if (not glfwInit()) {
            throw std::runtime_error{"Failed to init GLFW"};
        }

        glfwSetErrorCallback([](int, char const* message) {
            throw std::runtime_error{message};
        });
    }

    State::~State() noexcept {
        glfwTerminate();
    }

    auto State::get() -> State& {
        static auto instance = State{};
        return instance;
    }
}
