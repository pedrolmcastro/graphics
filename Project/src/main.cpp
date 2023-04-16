#include <iostream>

#include "math.hpp"
#include "render/init.hpp"
#include "windows/window.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};
    render::init();

    window.run([]{
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
}
