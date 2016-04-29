#version 330 core

// Inputs
in vec2 texture_coord;
in vec3 vertex_colour;

// Outputs
out vec4 out_colour;

// Uniforms
uniform sampler2D texture_sampler;

void main()
{
  // vec3 texture_colour = texture( texture_sampler, texture_coord ).rgb;

  // float gamma_correction = 1.0f / 2.2f;
  // vec3  gamma = vec3( gamma_correction,
  //                     gamma_correction,
  //                     gamma_correction );

  // vec3 final_colour = pow( texture_colour * vertex_colour, gamma );

  // out_colour = vec4( final_colour, 1.0f );

  out_colour = vec4( vertex_colour, 1.0f );
}