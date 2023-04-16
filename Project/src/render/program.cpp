#include <GL/glew.h>

#include "render/program.hpp"


namespace render {
    Program::~Program() noexcept {
        glDeleteProgram(code);
    }

    auto Program::attribute(GLchar const* name) const noexcept -> GLint {
        return glGetAttribLocation(code, name);
    }
}
