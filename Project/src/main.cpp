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
        // 1° Face
        { - 0.2f, - 0.2f, + 0.2f },
        { + 0.2f, - 0.2f, + 0.2f },
        { - 0.2f, + 0.2f, + 0.2f },
        { + 0.2f, + 0.2f, + 0.2f },

        // 2° Face
        { + 0.2f, - 0.2f, + 0.2f },
        { + 0.2f, - 0.2f, - 0.2f },
        { + 0.2f, + 0.2f, + 0.2f },
        { + 0.2f, + 0.2f, - 0.2f },

        // 3° Face
        { + 0.2f, - 0.2f, - 0.2f },
        { - 0.2f, - 0.2f, - 0.2f },
        { + 0.2f, + 0.2f, - 0.2f },
        { - 0.2f, + 0.2f, - 0.2f },

        // 4° Face
        { - 0.2f, - 0.2f, - 0.2f },
        { - 0.2f, - 0.2f, + 0.2f },
        { - 0.2f, + 0.2f, - 0.2f },
        { - 0.2f, + 0.2f, + 0.2f },

        // 5° Face
        { - 0.2f, - 0.2f, - 0.2f },
        { + 0.2f, - 0.2f, - 0.2f },
        { - 0.2f, - 0.2f, + 0.2f },
        { + 0.2f, - 0.2f, + 0.2f },

        // 6° Face
        { - 0.2f, + 0.2f, + 0.2f },
        { + 0.2f, + 0.2f, + 0.2f },
        { - 0.2f, + 0.2f, - 0.2f },
        { + 0.2f, + 0.2f, - 0.2f }
    };

    auto buffer = GLuint{0};
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto location = program.attribute("position");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), nullptr);


    auto transform = object::Transform{};

    window.run([program, &transform]() {
        render::clear(color::BLACK);


        transform.scale += 0.001f;
        transform.rotation += 0.01f;
        transform.translation.x += 0.001f;

        program.uniform("transform", object::transform(transform));


        program.uniform("color", color::RED);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        program.uniform("color", color::BLUE);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

        program.uniform("color", color::CYAN);
        glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);

        program.uniform("color", color::GREEN);
        glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);

        program.uniform("color", color::YELLOW);
        glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);

        program.uniform("color", color::MAGENTA);
        glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
    });
}
