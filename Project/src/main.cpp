/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#include "color.hpp"
#include "scene.hpp"
#include "render.hpp"
#include "windows.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};

    render::init("shaders/vertex.glsl", "shaders/fragment.glsl");
    window.onresize(render::viewport);


    auto scenes = scene::Scenes{window};

    window.run([&](windows::Timestep step) {
        render::clear(color::BLACK);
        scenes.update(step);
    });
}
