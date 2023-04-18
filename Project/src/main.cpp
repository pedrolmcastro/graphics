#include <iostream>

#include "math.hpp"
#include "color.hpp"
#include "object.hpp"
#include "render.hpp"
#include "windows.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};

    render::init();
    window.onresize(render::viewport);


    auto program = render::Program{
        render::Shader{GL_VERTEX_SHADER, std::filesystem::path{"shaders/vertex.glsl"}},
        render::Shader{GL_FRAGMENT_SHADER, std::filesystem::path{"shaders/fragment.glsl"}}
    };


    auto first = object::Cube{};
    first.transform.translation.x -= 0.5f;

    auto second = object::Cube{};
    second.transform.translation.x += 0.5f;


    window.run([program, &first, &second](windows::Timestep step) {
        render::clear(color::BLACK);

        first.transform.rotation += step.count();
        first.draw(program);

        second.transform.rotation += step.count();
        second.draw(program);
    });
}
