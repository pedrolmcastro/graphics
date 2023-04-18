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


    auto outline = object::Outline{};

    auto tetrahedron = object::Tetrahedron{};
    tetrahedron.transform.translation.x -= 0.5f;

    auto cube = object::Cube{};
    cube.transform.translation.y += 0.5f;

    auto hexagonal = object::Hexagonal{};
    hexagonal.transform.translation.y -= 0.5f;

    auto octahedron = object::Octahedron{};
    octahedron.transform.translation.x += 0.5f;


    window.run([&, program](windows::Timestep step) {
        render::clear(color::BLACK);

        cube.transform.rotation += step.count();
        hexagonal.transform.rotation += step.count();
        octahedron.transform.rotation += step.count();
        tetrahedron.transform.rotation += step.count();

        cube.draw(program);
        outline.draw(program);
        hexagonal.draw(program);
        octahedron.draw(program);
        tetrahedron.draw(program);
    });
}
