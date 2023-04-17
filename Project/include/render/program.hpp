#pragma once


#include <concepts>
#include <stdexcept>
#include <GL/glew.h>

#include "math.hpp"
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

        auto uniform(GLchar const* name, math::vec2 const& value) const noexcept -> void;
        auto uniform(GLchar const* name, math::vec3 const& value) const noexcept -> void;
        auto uniform(GLchar const* name, math::vec4 const& value) const noexcept -> void;
        auto uniform(GLchar const* name, math::mat2 const& value) const noexcept -> void;
        auto uniform(GLchar const* name, math::mat3 const& value) const noexcept -> void;
        auto uniform(GLchar const* name, math::mat4 const& value) const noexcept -> void;


    private:
        GLuint code = 0;
    };
}
