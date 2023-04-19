#pragma once


#include <GL/glew.h>
#include <filesystem>

#include "math.hpp"


namespace render {
    auto init(std::filesystem::path const& vertex, std::filesystem::path const& fragment) -> void;

    auto clear(math::vec3 const& color) noexcept -> void;
    auto viewport(math::ivec2 const& size) noexcept -> void;
}
