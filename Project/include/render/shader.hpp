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
