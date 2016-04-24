#ifndef ICE_GRAPHICS_MESH_HPP
#define ICE_GRAPHICS_MESH_HPP

#include <Ice/Common/OpenGL.hpp>
#include <Ice/Common/Common.hpp>

#include <Ice/Maths/Vec3.hpp>
#include <Ice/Maths/Vec2.hpp>

#include <Ice/Graphics/Shader.hpp>
#include <Ice/Graphics/Vertex.hpp>
#include <Ice/Graphics/Buffers.hpp>
#include <Ice/Graphics/Texture.hpp>

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