#pragma once


#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    template<class Drawer> struct Shape final {
        Transform transform;


        auto draw(render::Program const& program) const -> void {
            Drawer::get(program).draw(transform);
        }


        [[nodiscard]] auto& translation() noexcept {
            return transform.translation;
        }

        [[nodiscard]] auto& translation() const noexcept {
            return transform.translation;
        }

        [[nodiscard]] auto& rotation() noexcept {
            return transform.rotation;
        }

        [[nodiscard]] auto& rotation() const noexcept {
            return transform.rotation;
        }

        [[nodiscard]] auto& scale() noexcept {
            return transform.scale;
        }

        [[nodiscard]] auto& scale() const noexcept {
            return transform.scale;
        }
    };
}
