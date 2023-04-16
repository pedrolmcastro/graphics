#include <GL/glew.h>

#include <string>
#include <fstream>
#include <streambuf>
#include <stdexcept>
#include <filesystem>

#include "render/shader.hpp"


namespace render {
    auto Shader::compile(GLenum type, GLchar const* source) -> GLuint {
        auto code = glCreateShader(type);

        if (code == 0) {
            throw std::runtime_error{"Failed to create shader"};
        }


        glShaderSource(code, 1, &source, nullptr);
        glCompileShader(code);


        auto compiled = GLint{GL_FALSE};
        glGetShaderiv(code, GL_COMPILE_STATUS, &compiled);

        if (compiled == GL_FALSE) {
            auto length = GLint{0};
            glGetShaderiv(code, GL_INFO_LOG_LENGTH, &length);

            std::basic_string<GLchar> message;
            message.reserve(length + 1);
            glGetShaderInfoLog(code, length, nullptr, message.data());

            throw std::runtime_error{"Shader compilation failed: " + message};
        }

        return code;
    }


    Shader::Shader(GLenum type, GLchar const* source) {
        code = compile(type, source);
    }

    Shader::Shader(GLenum type, std::filesystem::path const& path) {
        auto file = std::ifstream{path};
        auto source = std::basic_string<GLchar>{std::istreambuf_iterator<GLchar>{file}, std::istreambuf_iterator<GLchar>{}};
        code = compile(type, source.c_str());
    }


    Shader::~Shader() noexcept {
        glDeleteShader(code);
    }
}
