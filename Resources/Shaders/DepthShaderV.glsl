uniform vec3 cameraPosition;

void main() {
    gl_Position = _MVP * vec4(in_Position, 1.0);
}
