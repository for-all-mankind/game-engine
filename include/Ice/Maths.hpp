#ifndef ICE_MATHS_DEFINES_H
#define ICE_MATHS_DEFINES_H

#include <Ice/Common/Types.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

namespace Ice
{
  const glm::vec2 Vec2_Zero  = glm::vec2( 0.0f, 0.0f );
  const glm::vec2 Vec2_One   = glm::vec2( 1.0f, 1.0f );
  const glm::vec2 Vec2_UnitX = glm::vec2( 1.0f, 0.0f );
  const glm::vec2 Vec2_UnitY = glm::vec2( 0.0f, 1.0f );

  const glm::vec3 Vec3_Zero  = glm::vec3( 0.0f, 0.0f, 0.0f );
  const glm::vec3 Vec3_One   = glm::vec3( 1.0f, 1.0f, 1.0f );
  const glm::vec3 Vec3_UnitX = glm::vec3( 1.0f, 0.0f, 0.0f );
  const glm::vec3 Vec3_UnitY = glm::vec3( 0.0f, 1.0f, 0.0f );
  const glm::vec3 Vec3_UnitZ = glm::vec3( 0.0f, 0.0f, 1.0f );

  const glm::vec4 Vec4_Zero  = glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f );
  const glm::vec4 Vec4_One   = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
  const glm::vec4 Vec4_UnitX = glm::vec4( 1.0f, 0.0f, 0.0f, 0.0f );
  const glm::vec4 Vec4_UnitY = glm::vec4( 0.0f, 1.0f, 0.0f, 0.0f );
  const glm::vec4 Vec4_UnitZ = glm::vec4( 0.0f, 0.0f, 1.0f, 0.0f );
  const glm::vec4 Vec4_UnitW = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f );
}

#endif // ICE_MATHS_DEFINES_H