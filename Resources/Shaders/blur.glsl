uniform sampler2D passThrough;

uniform int uBlurSize = 10; // use size of noise texture

in vec2 fragCoord; // input from vertex shader

out float fResult;

uniform vec2 dir;

void main() {
   vec2 texelSize = 1.0 / vec2(textureSize(passThrough, 0));
   float result = 0.0;
   vec2 hlim = vec2(float(-uBlurSize) * 0.5 + 0.5);
   for (int i = 0; i < uBlurSize; ++i) {
      for (int j = 0; j < uBlurSize; ++j) {
         vec2 offset = (hlim + vec2(float(i), float(j))) * texelSize;
         result += texture(passThrough, fragCoord + offset).r;
      }
   }
 
   fResult = result / float(uBlurSize * uBlurSize);
}
