#version 330 core

// Inputs
in vec2 texture_coord;

// Outputs
out vec4 colour;

// Uniforms
uniform sampler2D texture_sampler;
uniform vec3      box_colour;
uniform vec3      light_colour;

void main()
{
  colour = vec4( light_colour * box_colour, 1.0f );
}