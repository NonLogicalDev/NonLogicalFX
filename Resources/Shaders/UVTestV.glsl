out vec2 ex_TexCoord;

void main() {
    gl_Position = _MVP * vec4(in_Position, 1.0);
    ex_TexCoord = in_TexCoord;
}