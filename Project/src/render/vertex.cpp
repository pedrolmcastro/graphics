/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#include <GL/glew.h>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

#include "math.hpp"
#include "render/vertex.hpp"


namespace render {
    Vertex::Vertex(GLuint vertices, GLuint elements) noexcept : vertices{vertices}, elements{elements} {
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


    auto Vertex::attribute(GLint location, std::initializer_list<math::vec3> values) const -> void {
        if (values.size() != vertices) {
            throw std::runtime_error{"Wrong number of vertex data given to vertex array"};
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
        return reinterpret_cast<void const*>(size * sizeof(GLuint));
    }

    auto Vertex::triangles(GLuint count, GLuint offset) const -> void {
        if (count + offset > elements) {
            throw std::runtime_error{"Out of bounds draw"};
        }

        bind();
        glDrawElements(GL_TRIANGLES, count * 3, GL_UNSIGNED_INT, this->offset(offset * 3));
    }

    auto Vertex::lines(GLuint count, GLuint offset) const -> void {
        if (count + offset > elements) {
            throw std::runtime_error{"Out of bounds draw"};
        }

        bind();
        glDrawElements(GL_LINES, count * 2, GL_UNSIGNED_INT, this->offset(offset * 2));
    }
}
