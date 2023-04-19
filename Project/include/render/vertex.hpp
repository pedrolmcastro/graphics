#pragma once


#include <GL/glew.h>

#include <algorithm>
#include <type_traits>
#include <initializer_list>

#include "math.hpp"


namespace render {
    // Facade for OpenGL Vertex Array Object
    class Vertex final {
    public:
        Vertex(GLuint vertices, GLuint elements) noexcept;
        ~Vertex() noexcept;

        auto bind() const noexcept -> void;
        static auto unbind() noexcept -> void;


        template<class Element> requires(std::is_same_v<Element, math::uvec2> or std::is_same_v<Element, math::uvec3>)
        auto indices(std::initializer_list<Element> indices) const -> void {
            if (indices.size() != elements) {
                throw std::runtime_error{"Wrong number of indices given to vertex array"};
            }

            if (std::any_of(indices.begin(), indices.end(), [this](auto& indices) {
                return math::any(math::greaterThanEqual(indices, Element{this->vertices}));
            })) {
                throw std::runtime_error{"Out of bounds vertex index"};
            }


            bind();

            auto buffer = GLuint{0};
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(Element), std::data(indices), GL_STATIC_DRAW);
        }

        auto attribute(GLint location, std::initializer_list<math::vec3> values) const -> void;


        // Indices with math::uvec3 and attributes must be set before drawing triangles
        auto triangles(GLuint count, GLuint offset = 0) const -> void;

        // Indices with math::uvec2 and attributes must be set before drawing lines
        auto lines(GLuint count, GLuint offset = 0) const -> void;


    private:
        GLuint code = 0;
        GLuint vertices = 0; // Used for error checking
        GLuint elements = 0; // Used for error checking


        static auto offset(GLuint size) noexcept -> void const*;
    };
}
