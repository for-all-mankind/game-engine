#ifndef ICE_VERTEX_H
#define ICE_VERTEX_H

#include <cstddef>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Ice
{
  struct Vertex
  {
    glm::vec3 position;
    glm::vec3 colour;
    glm::vec2 tex_coord;
  };

  #define VERTEX_SIZE           sizeof( Vertex )
  #define VERTEX_SIZE_POSITION  3
  #define VERTEX_SIZE_COLOUR    3
  #define VERTEX_SIZE_TEX_COORD 2

  #define VERTEX_OFFSET_POSITION  (GLvoid*) offsetof( Vertex, position  )
  #define VERTEX_OFFSET_COLOUR    (GLvoid*) offsetof( Vertex, colour    )
  #define VERTEX_OFFSET_TEX_COORD (GLvoid*) offsetof( Vertex, tex_coord )
}

#endif // ICE_VERTEX_H