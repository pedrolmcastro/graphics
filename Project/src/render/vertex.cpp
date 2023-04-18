#include <GL/glew.h>
#include <stdexcept>
#include <initializer_list>

#include "math.hpp"
#include "render/vertex.hpp"


namespace render {
    Vertex::Vertex() noexcept {
        glGenVertexArrays(1, &code);
        bind();
    }

    Vertex::~Vertex() noexcept {
        glDeleteVertexArrays(1, &code);
    }


    auto Vertex::bind() const noexcept -> void {
        glBindVertexArray(code);
    }

    auto Vertex::unbind() noexcept -> void {
        glBindVertexArray(0);
    }


    auto Vertex::indices(std::initializer_list<math::uvec3> indices) noexcept -> void {
        bind();

        auto buffer = GLuint{0};
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(math::uvec3), std::data(indices), GL_STATIC_DRAW);

        elements = indices.size();
    }

    auto Vertex::attribute(GLint location, std::initializer_list<math::vec3> values) const noexcept -> void {
        bind();

        auto buffer = GLuint{0};
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(math::vec3), std::data(values), GL_STATIC_DRAW);

        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), nullptr);
    }


    auto Vertex::offset(GLuint size) noexcept -> void const* {
        return reinterpret_cast<void const*>(size * 3 * sizeof(GLuint));
    }

    auto Vertex::draw(GLuint triangles, GLuint offset) const -> void {
        if (offset + triangles > elements) {
            throw std::runtime_error{"Out of bounds draw"};
        }

        bind();
        glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_INT, this->offset(offset));
    }
}
