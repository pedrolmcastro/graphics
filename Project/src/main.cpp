#include <iostream>

#include "math.hpp"


auto main() -> int {
    auto vec = math::vec4{1.0f, 2.0f, 3.0f, 4.0f};
    std::cout << math::to_string(vec) << std::endl;
}
