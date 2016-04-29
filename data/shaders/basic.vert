#version 330 core

// Inputs
layout ( location = 0 ) in vec3 in_position;
layout ( location = 1 ) in vec3 in_normals;
layout ( location = 2 ) in vec4 in_colour;
layout ( location = 3 ) in vec2 in_texture_coord;

// Outputs
out vec4 vertex_colour;
out vec2 texture_coord;

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  vertex_colour = in_colour;
  texture_coord = in_texture_coord;

  // gl_Position = projection * view * model * vec4( in_position, 1.0f );
  gl_Position = view * model * vec4( in_position, 1.0f );
}