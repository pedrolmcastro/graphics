#pragma once


#include <GL/glew.h>

#include "math.hpp"


namespace render {
    auto init() -> void;

    auto clear(math::vec3 const& color) noexcept -> void;
    auto viewport(math::ivec2 const& size) noexcept -> void;
}
