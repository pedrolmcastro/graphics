#pragma once


#include <GL/glew.h>
#include <initializer_list>

#include "math.hpp"


namespace render {
    // Facade for OpenGL Vertex Array Object
    class Vertex final {
    public:
        Vertex() noexcept;
        ~Vertex() noexcept;

        auto bind() const noexcept -> void;
        static auto unbind() noexcept -> void;

        auto indices(std::initializer_list<math::uvec3> indices) noexcept -> void;
        auto attribute(GLint location, std::initializer_list<math::vec3> values) const noexcept -> void;

        // Indices and attributes must be set before calling draw
        auto draw(GLuint triangles, GLuint offset = 0) const -> void;


    private:
        GLuint code = 0;
        GLuint elements = 0;

        static auto offset(GLuint size) noexcept -> void const*;
    };
}
