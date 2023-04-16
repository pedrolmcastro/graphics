#include <mutex>
#include <stdexcept>
#include <GL/glew.h>

#include "render/init.hpp"


namespace render {
    auto init() -> void {
        static auto flag = std::once_flag{};
        
        std::call_once(flag, []{
            if (glewInit() != GLEW_OK) {
                throw std::runtime_error{"Failed to init GLEW"};
            }
        });
    }
}
