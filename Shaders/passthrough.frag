////////////////////////////////////////////////////////////////////////////////
// Simple pass through fragment shader, i.e., simply set the required gl data --
// the fragment color.
////////////////////////////////////////////////////////////////////////////////

#version 330

in  vec4  color; // Interpolated color from rasterization step
out vec4 fcolor; // Output fragment color

void main() {
  fcolor = color;
}
