/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include <GL/glew.h>
#include <filesystem>

#include "math.hpp"


namespace render {
    auto init(std::filesystem::path const& vertex, std::filesystem::path const& fragment) -> void;

    auto clear(math::vec3 const& color) noexcept -> void;
    auto viewport(math::ivec2 const& size) noexcept -> void;
}
