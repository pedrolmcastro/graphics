#include <GL/glew.h>

#include "math.hpp"
#include "render/program.hpp"


namespace render {
    Program::~Program() noexcept {
        glDeleteProgram(code);
    }


    auto Program::attribute(GLchar const* name) const noexcept -> GLint {
        return glGetAttribLocation(code, name);
    }


    auto Program::uniform(GLchar const* name, math::vec2 const& value) const noexcept -> void {
        glUniform2fv(glGetUniformLocation(code, name), 1, math::value_ptr(value));
    }

    auto Program::uniform(GLchar const* name, math::vec3 const& value) const noexcept -> void {
        glUniform3fv(glGetUniformLocation(code, name), 1, math::value_ptr(value));
    }

    auto Program::uniform(GLchar const* name, math::vec4 const& value) const noexcept -> void {
        glUniform4fv(glGetUniformLocation(code, name), 1, math::value_ptr(value));
    }

    auto Program::uniform(GLchar const* name, math::mat2 const& value) const noexcept -> void {
        glUniformMatrix2fv(glGetUniformLocation(code, name), 1, GL_FALSE, math::value_ptr(value));
    }

    auto Program::uniform(GLchar const* name, math::mat3 const& value) const noexcept -> void {
        glUniformMatrix3fv(glGetUniformLocation(code, name), 1, GL_FALSE, math::value_ptr(value));
    }

    auto Program::uniform(GLchar const* name, math::mat4 const& value) const noexcept -> void {
        glUniformMatrix4fv(glGetUniformLocation(code, name), 1, GL_FALSE, math::value_ptr(value));
    }
}
