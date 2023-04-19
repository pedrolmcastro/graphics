#include "color.hpp"
#include "scene.hpp"
#include "render.hpp"
#include "windows.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};

    render::init("shaders/vertex.glsl", "shaders/fragment.glsl");
    window.onresize(render::viewport);


    auto scenes = scene::Scenes{window, {scene::Scale{}, scene::Translate{}, scene::Rotate{}}};

    window.run([&](windows::Timestep step) {
        render::clear(color::BLACK);
        scenes.update(step);
    });
}
