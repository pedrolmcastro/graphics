#pragma once


#include <concepts>
#include <stdexcept>
#include <GL/glew.h>

#include "render/shader.hpp"


namespace render {
    class Program final {
    public:
        Program(std::same_as<Shader> auto&& ... shaders) {
            code = glCreateProgram();

            if (code == 0) {
                std::runtime_error{"Failed to create OpenGL program"};
            }

            (glAttachShader(code, shaders.code) , ...);

            glLinkProgram(code);
            glUseProgram(code);
        }

        ~Program() noexcept;


        [[nodiscard]] auto attribute(GLchar const* name) const noexcept -> GLint;


    private:
        GLuint code = 0;
    };
}
