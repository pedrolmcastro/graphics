/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#pragma once


#include "render/program.hpp"
#include "object/transform.hpp"


namespace object {
    template<class Drawer> struct Shape final {
        Transform transform;


        auto draw() const -> void {
            Drawer::draw(transform);
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
