#ifndef ICE_GRAPHICS_MESH_HPP
#define ICE_GRAPHICS_MESH_HPP

#include "OpenGL.hpp"
#include "Common.hpp"

#include "Vec3.hpp"
#include "Vec2.hpp"

#include "Shader.hpp"
#include "Vertex.hpp"
#include "Buffers.hpp"
#include "Texture.hpp"

namespace Ice
{
  class Mesh
  {
  public:
    void AddData( std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures );
    void Draw( Shader& shader );

  private:
    void SetupMesh();

  private:
    GLvao _vao;

    std::vector<Vertex>  _vertices;
    std::vector<GLuint>  _indices;
    std::vector<Texture> _textures;
  };
}


#endif // ICE_GRAPHICS_MESH_HPP