#include <iostream>

#include "math.hpp"
#include "color.hpp"
#include "render/shader.hpp"
#include "render/vertex.hpp"
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


    auto vertex = render::Vertex{};

    vertex.attribute(program.location("a_Position"), {
        { - 0.1f, - 0.1f, - 0.1f }, // 0
        { - 0.1f, - 0.1f, + 0.1f }, // 1
        { - 0.1f, + 0.1f, - 0.1f }, // 2
        { - 0.1f, + 0.1f, + 0.1f }, // 3
        { + 0.1f, - 0.1f, - 0.1f }, // 4
        { + 0.1f, - 0.1f, + 0.1f }, // 5
        { + 0.1f, + 0.1f, - 0.1f }, // 6
        { + 0.1f, + 0.1f, + 0.1f }, // 7
    });

    vertex.indices({
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
    });


    auto transform = object::Transform{};

    window.run([program, vertex, &transform](windows::Timestep step) {
        render::clear(color::BLACK);

        transform.rotation += step.count();
        program.uniform("u_Transform", object::transform(transform));


        program.uniform("u_Color", color::RED);
        vertex.draw(2);

        program.uniform("u_Color", color::MAGENTA);
        vertex.draw(2, 2);

        program.uniform("u_Color", color::GREEN);
        vertex.draw(2, 4);

        program.uniform("u_Color", color::YELLOW);
        vertex.draw(2, 6);

        program.uniform("u_Color", color::BLUE);
        vertex.draw(2, 8);

        program.uniform("u_Color", color::CYAN);
        vertex.draw(2, 10);
    });
}
