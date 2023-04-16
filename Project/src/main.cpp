#include "math.hpp"
#include "render/init.hpp"
#include "render/shader.hpp"
#include "render/program.hpp"
#include "windows/window.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};
    render::init();


    auto program = render::Program{
        render::Shader{GL_VERTEX_SHADER, std::filesystem::path{"shaders/vertex.glsl"}},
        render::Shader{GL_FRAGMENT_SHADER, std::filesystem::path{"shaders/fragment.glsl"}}
    };


    math::vec2 vertices[] = {
        { - 0.5f, - 0.5f },
        { + 0.5f, - 0.5f },
        { + 0.0f, + 0.5f },
    };

    auto buffer = GLuint{0};
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto location = program.attribute("position");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), nullptr);


    window.run([]{
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    });
}
