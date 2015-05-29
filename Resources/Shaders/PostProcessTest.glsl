in vec2 fragCoord;

uniform sampler2D passThrough;
uniform int iDirection;

float noise(vec2 p) {
  float k = fract(p.x);
  float v = fract(p.y);
  return 0.0035 * k + 0.05 * sin(v) * (k + 0.01);
}

void main() {
  vec2 uv = fragCoord;
  vec4 pC = texture(passThrough, uv);

  vec2 dir;
  float step = 0.0015;
  if (iDirection == 1) {
    dir = vec2(step, 0.0);
  } else {
    dir = vec2(0.0, step);
  }

  int samples = 30;
  vec4 sum = vec4(0.0);
  for(int i = -samples/2; i <= samples/2; i++) {
    float w = abs(i/float(samples))/2.0;
    vec2 sampler = uv + i * dir;
    sum +=  0.3 * w * texture(passThrough, sampler);
  }

  sum.a = 1.0;
  ex_fragColor = sum;
}
