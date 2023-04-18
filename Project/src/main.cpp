#include <iostream>

#include "math.hpp"
#include "color.hpp"
#include "render/shader.hpp"
#include "render/command.hpp"
#include "render/program.hpp"
#include "windows/window.hpp"
#include "object/transform.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};

    render::init();
    window.onresize(render::viewport);


    auto program = render::Program{
        render::Shader{GL_VERTEX_SHADER, std::filesystem::path{"shaders/vertex.glsl"}},
        render::Shader{GL_FRAGMENT_SHADER, std::filesystem::path{"shaders/fragment.glsl"}}
    };


    math::vec3 vertices[] = {
        { - 0.1f, - 0.1f, - 0.1f }, // 0
        { - 0.1f, - 0.1f, + 0.1f }, // 1
        { - 0.1f, + 0.1f, - 0.1f }, // 2
        { - 0.1f, + 0.1f, + 0.1f }, // 3
        { + 0.1f, - 0.1f, - 0.1f }, // 4
        { + 0.1f, - 0.1f, + 0.1f }, // 5
        { + 0.1f, + 0.1f, - 0.1f }, // 6
        { + 0.1f, + 0.1f, + 0.1f }, // 7
    };

    math::uvec3 indices[] = {
        // Front
        {0, 4, 6},
        {6, 2, 0},

        // Back
        {5, 1, 3},
        {3, 7, 5},

        // Right
        {4, 5, 7},
        {7, 6, 4},

        // Left
        {1, 0, 2},
        {2, 3, 1},

        // Top
        {2, 6, 7},
        {7, 3, 2},

        // Bottom
        {1, 5, 4},
        {4, 0, 1},
    };


    auto array = GLuint{0};
    glGenVertexArrays(1, &array);
    glBindVertexArray(array);

    auto buffer = GLuint{0};
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto location = program.attribute("a_Position");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    auto elements = GLuint{0};
    glGenBuffers(1, &elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);


    auto transform = object::Transform{};

    window.run([program, array, &transform](windows::Timestep) {
        render::clear(color::BLACK);

        transform.rotation += 0.01f;
        program.uniform("u_Transform", object::transform(transform));


        glBindVertexArray(array);

        program.uniform("u_Color", color::RED);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        program.uniform("u_Color", color::MAGENTA);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void const*>(6 * sizeof(GLuint)));

        program.uniform("u_Color", color::GREEN);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void const*>(12 * sizeof(GLuint)));

        program.uniform("u_Color", color::YELLOW);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void const*>(18 * sizeof(GLuint)));

        program.uniform("u_Color", color::BLUE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void const*>(24 * sizeof(GLuint)));

        program.uniform("u_Color", color::CYAN);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void const*>(30 * sizeof(GLuint)));
    });
}
