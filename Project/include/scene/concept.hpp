#pragma once


#include <concepts>
#include <type_traits>

#include "windows/window.hpp"


namespace scene {
    template<class Type> concept Scene = std::move_constructible<Type> and requires(Type scene, windows::Window& window, windows::Timestep step) {
        { scene.start(window) };
        { scene.update(window, step) } -> std::convertible_to<bool>;
    };
}
