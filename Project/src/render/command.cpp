#include <mutex>
#include <stdexcept>
#include <GL/glew.h>

#include "math.hpp"
#include "render/command.hpp"


namespace render {
    auto init() -> void {
        static auto flag = std::once_flag{};

        std::call_once(flag, []{
            if (glewInit() != GLEW_OK) {
                throw std::runtime_error{"Failed to init GLEW"};
            }
        });

        glEnable(GL_DEPTH_TEST);
    }


    auto clear(math::vec3 const& color) noexcept -> void {
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }


    auto viewport(math::ivec2 const& size) noexcept -> void {
        glViewport(0, 0, size.x, size.y);
    }
}
