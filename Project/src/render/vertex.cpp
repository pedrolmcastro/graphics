#include <GL/glew.h>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

#include "math.hpp"
#include "render/vertex.hpp"


namespace render {
    Vertex::Vertex(GLuint vertices, GLuint triangles) noexcept : vertices{vertices}, triangles{triangles} {
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


    auto Vertex::indices(std::initializer_list<math::uvec3> indices) const -> void {
        if (indices.size() != triangles) {
            throw std::runtime_error{"Wrong number of triangles given to Vertex Array"};
        }

        if (std::any_of(indices.begin(), indices.end(), [this](math::uvec3 const& indices) {
            return indices.x >= this->vertices || indices.y >= this->vertices || indices.z >= this->vertices;
        })) {
            throw std::runtime_error{"Out of bounds vertex in triangle indices"};
        }


        bind();

        auto buffer = GLuint{0};
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles * sizeof(math::uvec3), std::data(indices), GL_STATIC_DRAW);
    }

    auto Vertex::attribute(GLint location, std::initializer_list<math::vec3> values) const -> void {
        if (values.size() != vertices) {
            throw std::runtime_error{"Wrong number of vertex data given to Vertex Array"};
        }


        bind();

        auto buffer = GLuint{0};
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(math::vec3), std::data(values), GL_STATIC_DRAW);

        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), nullptr);
    }


    auto Vertex::offset(GLuint size) noexcept -> void const* {
        return reinterpret_cast<void const*>(size * 3 * sizeof(GLuint));
    }

    auto Vertex::draw(GLuint triangles, GLuint offset) const -> void {
        if (triangles + offset > this->triangles) {
            throw std::runtime_error{"Out of bounds draw"};
        }

        bind();
        glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_INT, this->offset(offset));
    }
}
