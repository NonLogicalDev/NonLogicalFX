in vec2 fragCoord;

uniform sampler2D diffuseMap;
uniform sampler2D occlusionMap;
uniform sampler2D shadowMap;
uniform sampler2D lightMap;

void main() {
  vec3 diffuseC = texture(diffuseMap, fragCoord).rgb;
  float ambientC = texture(occlusionMap, fragCoord).r;

  float o = clamp(0,1,ambientC * 1.7);

  ex_fragColor = vec4(diffuseC * o, 1.0);
}
