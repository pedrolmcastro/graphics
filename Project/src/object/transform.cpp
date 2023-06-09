/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


#include "math.hpp"
#include "object/transform.hpp"


namespace object {
    auto rotation(Transform const& transform) -> math::mat4 {
        return (
            math::rotate(transform.rotation.x, math::vec3{1.0f, 0.0f, 0.0f}) * // Around x
            math::rotate(transform.rotation.y, math::vec3{0.0f, 1.0f, 0.0f}) * // Around y
            math::rotate(transform.rotation.z, math::vec3{0.0f, 0.0f, 1.0f})   // Around z
        );
    }

    auto transform(Transform const& transform) -> math::mat4 {
        return math::translate(transform.translation) * rotation(transform) * math::scale(math::vec3{transform.scale});
    }
}
