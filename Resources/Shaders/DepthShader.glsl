//!! vertex:
uniform vec3 cameraPosition;

void main() {
    gl_Position = _MVP * vec4(in_Position, 1.0);
}

//!! fragment:
void main() {
    ex_fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
