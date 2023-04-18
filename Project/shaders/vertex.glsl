attribute vec3 a_Position;
uniform mat4 u_Transform;

void main() {
    gl_Position = u_Transform * vec4(a_Position, 1.0);
}
