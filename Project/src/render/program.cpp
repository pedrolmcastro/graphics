#include <GL/glew.h>

#include "math.hpp"
#include "render/program.hpp"


namespace render {
    Program::Program(GLuint code) : code{code} {
        if (code == 0) {
            throw std::runtime_error{"Failed to create OpenGL program"};
        }
    }

    Program::~Program() noexcept {
        glDeleteProgram(code);
    }

    auto Program::get() -> Program& {
        static auto instance = Program{glCreateProgram()};
        return instance;
    }


    auto Program::shader(Shader&& shader) noexcept -> void {
        glAttachShader(get().code, shader.code);
    }

    auto Program::use() noexcept -> void {
        glLinkProgram(get().code);
        glUseProgram(get().code);
    }


    auto Program::location(GLchar const* name) noexcept -> GLint {
        return glGetAttribLocation(get().code, name);
    }


    auto Program::uniform(GLchar const* name, math::vec3 const& value) noexcept -> void {
        glUniform3fv(glGetUniformLocation(get().code, name), 1, math::value_ptr(value));
    }

    auto Program::uniform(GLchar const* name, math::mat4 const& value) noexcept -> void {
        glUniformMatrix4fv(glGetUniformLocation(get().code, name), 1, GL_FALSE, math::value_ptr(value));
    }
}
