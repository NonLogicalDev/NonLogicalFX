in vec2 fragCoord;

uniform sampler2D passThrough;
uniform sampler2D depthMap;
uniform int iDirection;

float noise(vec2 p) {
  float k = fract(p.x);
  float v = fract(p.y);
  return 0.0035 * k + 0.05 * sin(v) * (k + 0.01);
}

vec3 GaussianBlur( sampler2D tex0, vec2 centreUV, vec2 halfPixelOffset, vec2 pixelOffset )
{
    vec3 colOut = vec3( 0, 0, 0 );
                                 
    ////////////////////////////////////////////////;
    // Kernel width 7 x 7

    const int stepCount = 2;

    /* const float gWeights[2] = { */
    /*    0.44908, 0.05092 */
    /* }; */

    /* const float gOffsets[2] = { */
    /*    0.53805, 2.06278 */
    /* }; */

    ////////////////////////////////////////////////;

    /* for( int i = 0; i < stepCount; i++ ) {                        */
    /*     vec2 texCoordOffset = gOffsets[i] * pixelOffset; */
    /*     vec3 col = texture( tex0, centreUV + texCoordOffset ).xyz +  */
    /*                texture( tex0, centreUV – texCoordOffset ).xyz;  */
    /*     colOut += gWeights[i] * col; */
    /* } */

    return colOut;
}                       

void main() {
  float depth = abs(1.0 - (1.0 - texture(depthMap, fragCoord).r) * 10.0);
  vec2 uv = fragCoord;
  vec4 pC = texture(passThrough, uv);

  vec2 dir;
  float step = 0.002 * depth;
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
