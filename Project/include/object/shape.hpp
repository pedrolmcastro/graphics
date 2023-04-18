#pragma once


#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    template<class Drawer> struct Shape final {
        Transform transform;

        auto draw(render::Program const& program) const -> void {
            Drawer::get(program).draw(transform);
        }
    };
}
