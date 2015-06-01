in vec2 fragCoord;

uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform sampler2D noiseMap;
uniform int _SampleKernelSize = 60;
uniform vec3 _SampleKernel[80];
//uniform float _Radius;

uniform mat4 unProj;

float getDepth(vec2 uv) {
  float z = texture(depthMap, uv).r;
  return z;
}

vec3 getNormal() {
  vec3 n = texture(normalMap, fragCoord).rgb * 2.0 - 1.0;
  return normalize(n);
}

vec3 getViewPosition() {
  float x = (1.0-fragCoord.x) * 2 - 1.0;
  float y = (1.0 - fragCoord.y) * 2 - 1.0;
  float z = -getDepth(fragCoord);

  vec4 projPos  = vec4(x,y,z,1.0);
  vec4 p = unProj * projPos;
  p = p/p.w;
  p.z = -z;

  return p.xyz;
}

void main() {
  ivec2 noiseSize = textureSize(noiseMap, 0);
  float noiseScale = (iResolution.x/noiseSize.x);

  vec3  origin = getViewPosition();
  vec3  normal = getNormal();

  vec3 rvec = texture(noiseMap, fragCoord * noiseScale).xyz * 2.0 - 1.0;
  vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
  vec3 bitangent = cross(normal, tangent);
  mat3 tbn = mat3(tangent, bitangent, normal);

  float _Radius = 0.1;
  float occlusion = 0.0;
  for (int i = 0; i < _SampleKernelSize; ++i) {
    // get aSample position:
    vec3 aSample = tbn * _SampleKernel[i];
    aSample = aSample * _Radius + origin;

    // project aSample position:
    vec4 aOffset = vec4(aSample, 1.0);
    aOffset = _Projection * aOffset;
    aOffset.xy /= aOffset.w;
    aOffset.xy = aOffset.xy * 0.5 + 0.5;

    // get aSample depth:
    float sampleDepth = getDepth(aOffset.xy);

    // range check & accumulate:
    float rangeCheck= abs(origin.z - sampleDepth) < _Radius ? 1.0 : 0.0;
    occlusion += (sampleDepth <= aSample.z ? 1.0 : 0.0) * rangeCheck;
  }

  occlusion = 1.0 - (occlusion / _SampleKernelSize);
  float o = occlusion;
  ex_fragColor = vec4(o,o,o,1.0);
}
