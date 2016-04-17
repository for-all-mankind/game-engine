#version 330 core

// Inputs
in vec4 vertex_colour;
in vec2 texture_coord;

// Outputs
out vec4 colour;

// Uniforms
uniform sampler2D texture_sampler;

void main()
{
  colour = texture( texture_sampler, texture_coord ) * vertex_colour;
}