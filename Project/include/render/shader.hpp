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


namespace render {
    class Shader final {
    public:
        friend class Program;

        Shader(GLenum type, GLchar const* source);
        Shader(GLenum type, std::filesystem::path const& path);

        ~Shader() noexcept;


    private:
        GLuint code = 0;

        [[nodiscard]] static auto compile(GLenum type, GLchar const* source) -> GLuint;
    };
}
