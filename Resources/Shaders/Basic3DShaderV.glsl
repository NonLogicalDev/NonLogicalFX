out vec2 ex_texCoord;

void main() {
    vec4 position = _MVP * vec4(in_Position, 1.0);
    gl_Position = position;
    ex_texCoord = in_TexCoord;
}