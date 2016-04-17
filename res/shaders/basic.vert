#version 330 core

// Inputs
layout ( location = 0 ) in vec3 in_position;
layout ( location = 1 ) in vec3 in_colour;
layout ( location = 2 ) in vec2 in_texture_coord;

// Outputs
out vec4 vertex_colour;
out vec2 texture_coord;

// Uniforms
uniform mat4 transform;

void main()
{
  gl_Position   = transform * vec4( in_position, 1.0f );
  vertex_colour = vec4( in_colour  , 1.0f );
  texture_coord = in_texture_coord;
}