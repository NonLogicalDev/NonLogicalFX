//!! vertex:
void main(void) {
    gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
}

//!! fragment:
void main(void) {
    // Pass through our original color with full opacity.
    ex_fragColor = vec4(1.0,1.0,1.0,1.0);
}
