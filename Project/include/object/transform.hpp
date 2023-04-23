/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


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
