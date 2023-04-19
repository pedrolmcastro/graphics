#include <iostream>

#include "math.hpp"
#include "color.hpp"
#include "object.hpp"
#include "render.hpp"
#include "windows.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};

    render::init("shaders/vertex.glsl", "shaders/fragment.glsl");
    window.onresize(render::viewport);


    auto outline = object::Outline{};
    auto cube = object::Cube{{ .translation = {0.0f, 0.5f, 0.0f} }};
    auto hexagonal = object::Hexagonal{{ .translation = {0.0f, - 0.5f, 0.0f} }};
    auto octahedron = object::Octahedron{{ .translation = {0.5f, 0.0f, 0.0f} }};
    auto tetrahedron = object::Tetrahedron{{ .translation = {- 0.5f, 0.0f, 0.0f} }};


    window.run([&](windows::Timestep step) {
        render::clear(color::BLACK);

        cube.rotation() += step.count();
        hexagonal.rotation() += step.count();
        octahedron.rotation() += step.count();
        tetrahedron.rotation() += step.count();

        cube.draw();
        outline.draw();
        hexagonal.draw();
        octahedron.draw();
        tetrahedron.draw();
    });
}
