attribute vec4 a_Vertex;

uniform mat4 u_Matrix;
uniform float u_PointSize;

void main(void) {
  gl_Position = u_Matrix * a_Vertex;
  gl_PointSize = u_PointSize;
}
