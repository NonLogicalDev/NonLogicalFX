//!! vertex:
out vec2 ex_TexCoord;

void main() {
    gl_Position = _MVP * vec4(in_Position, 1.0);
    ex_TexCoord = in_TexCoord;
}

//!! fragment:
in vec2 ex_TexCoord;
uniform sampler2D uvTexture;

void main() {
   vec2 uv = ex_TexCoord;
   //uv.x += 0.1 * sin(iGlobalTime);
   ex_fragColor = texture(uvTexture, uv);
}
