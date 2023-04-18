#pragma once


#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    class Cube final {
    public:
        Transform transform;

        // This function assumes the existence of "a_Position", "u_Transform" and "u_Color" in the shaders
        auto draw(render::Program const& program) const noexcept -> void;


    private:
        // Singleton for the cubes vertex arrays
        class Drawer;
    };
}
