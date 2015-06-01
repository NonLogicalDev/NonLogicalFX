//!! vertex:
out vec4 vx_normal;

void main() {
  vx_normal = _MVP  * vec4(in_Normal, 1.0);
  gl_Position = _MVP * vec4(in_Position, 1.0);
}

//!! fragment:
in vec4 vx_normal;

void main() {
  ex_fragColor = vec4(vx_normal.x,vx_normal.y,vx_normal.z,1.0);
}
