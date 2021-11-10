////////////////////////////////////////////////////////////////////////////////
// Simple pass through vertex shader, i.e., do not alter anything about the
// position, simply set the required gl data. Additionally, pass along the color
// data about the vertex.
////////////////////////////////////////////////////////////////////////////////

#version 330

 in vec4   vpos; // Input vertex position from data
 in vec4 vcolor; // Input vertex color from data
out vec4  color; // Assigned vertex color to send to rasterizer

void main() {
  gl_Position = vpos;
  color = vcolor;
}
