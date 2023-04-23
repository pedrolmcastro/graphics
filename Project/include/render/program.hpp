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
#include "render/shader.hpp"


namespace render {
    // Singleton facade for OpenGL program
    class Program final {
    public:
        friend auto init(std::filesystem::path const& vertex, std::filesystem::path const& fragment) -> void;


        static auto get() -> Program&;

        ~Program() noexcept;


        [[nodiscard]] static auto location(GLchar const* name) noexcept -> GLint;

        static auto uniform(GLchar const* name, math::vec3 const& value) noexcept -> void;
        static auto uniform(GLchar const* name, math::mat4 const& value) noexcept -> void;


    private:
        Program(GLuint code);
        Program(Program const&) = delete;


        static auto use() noexcept -> void;
        static auto shader(Shader&& shader) noexcept -> void;


        GLuint code = 0;
    };
}
