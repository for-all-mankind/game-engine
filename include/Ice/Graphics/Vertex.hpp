#ifndef ICE_VERTEX_H
#define ICE_VERTEX_H

#include <Ice/Common/Types.hpp>
#include <Ice/Common/OpenGL.hpp>
#include <Ice/Common/Common.hpp>
#include <Ice/Maths/Maths.hpp>
#include <Ice/Graphics/Colour.hpp>

namespace Ice
{
  struct Vertex
  {
    Vec3   position;
    Vec3   normal;
    Colour colour;
    Vec2   tex_coord;
  };

  #define VERTEX_SIZE sizeof( Vertex )

  #define V_COMPONENTS_P 3
  #define V_TYPE_P       GL_FLOAT
  #define V_NORMALISE_P  GL_FALSE
  #define V_OFFSET_P     (GLvoid*) offsetof( Vertex, position )

  #define V_COMPONENTS_N 3
  #define V_TYPE_N       GL_FLOAT
  #define V_NORMALISE_N  GL_FALSE
  #define V_OFFSET_N     (GLvoid*) offsetof( Vertex, normal )

  #define V_COMPONENTS_C 4
  #define V_TYPE_C       GL_UNSIGNED_BYTE
  #define V_NORMALISE_C  GL_TRUE
  #define V_OFFSET_C     (GLvoid*) offsetof( Vertex, colour )

  #define V_COMPONENTS_T 2
  #define V_TYPE_T       GL_FLOAT
  #define V_NORMALISE_T  GL_FALSE
  #define V_OFFSET_T     (GLvoid*) offsetof( Vertex, tex_coord )
}

#endif // ICE_VERTEX_H