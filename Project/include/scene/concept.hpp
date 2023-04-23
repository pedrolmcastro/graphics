/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include <concepts>
#include <type_traits>

#include "windows/window.hpp"


namespace scene {
    template<class Type> concept Scene = std::is_default_constructible_v<Type> and requires(Type scene, windows::Window& window, windows::Timestep step) {
        { scene.start(window) };
        { scene.update(window, step) } -> std::convertible_to<bool>;
    };
}
