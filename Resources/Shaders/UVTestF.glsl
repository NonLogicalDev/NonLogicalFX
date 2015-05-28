in vec2 ex_TexCoord;
uniform sampler2D uvTexture;

void main() {
   ex_fragColor = texture(uvTexture, ex_TexCoord);
}