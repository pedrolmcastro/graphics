#include <iostream>

#include "math.hpp"
#include "windows/window.hpp"


auto main() -> int {
    auto window = windows::Window{"Window", {500, 500}};
    window.run([]{});
}
