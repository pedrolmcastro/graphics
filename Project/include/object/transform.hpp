#pragma once


#include "math.hpp"


namespace object {
    struct Transform final {
        float scale = 1.0f;
        math::vec3 rotation; // Euler angles
        math::vec3 translation;
    };


    [[nodiscard]] auto rotation(Transform const& transform) -> math::mat4;
    [[nodiscard]] auto transform(Transform const& transform) -> math::mat4;
}
