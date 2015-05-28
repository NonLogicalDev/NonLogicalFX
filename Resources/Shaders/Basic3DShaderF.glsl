in vec2 ex_texCoord;

uniform sampler2D baseTexture;

void main() {
    ex_fragColor = texture(baseTexture, ex_texCoord);
}
