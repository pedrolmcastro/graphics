/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


attribute vec3 a_Position;
uniform mat4 u_Transform;

void main() {
    gl_Position = u_Transform * vec4(a_Position, 1.0);
}
