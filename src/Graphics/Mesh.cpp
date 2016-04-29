#include <Ice/Graphics/Mesh.hpp>

namespace Ice
{
  void Mesh::AddData( std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures )
  {
    _vertices = std::move( vertices );
    _indices  = std::move( indices  );
    _textures = std::move( textures );

    SetupMesh();
  }

  void Mesh::SetupMesh()
  {
    _vao.Bind();

    _vao.VBO().Bind();
    _vao.VBO().BufferData( _vertices.size() * VERTEX_SIZE, _vertices.data(), GL_STATIC_DRAW );

    _vao.EBO().Bind();
    _vao.EBO().BufferData( _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW );

    //Vertex positions
    _vao.SetVAP( 0, V_COMPONENTS_P, V_TYPE_P, V_NORMALISE_P, VERTEX_SIZE, V_OFFSET_P );
    _vao.SetVAP( 1, V_COMPONENTS_N, V_TYPE_N, V_NORMALISE_N, VERTEX_SIZE, V_OFFSET_N );
    _vao.SetVAP( 2, V_COMPONENTS_C, V_TYPE_C, V_NORMALISE_C, VERTEX_SIZE, V_OFFSET_C );
    _vao.SetVAP( 3, V_COMPONENTS_T, V_TYPE_T, V_NORMALISE_T, VERTEX_SIZE, V_OFFSET_T );

    _vao.UnBind();
  }

  void Mesh::Draw( Shader& shader )
  {
    GLuint diffuseNr  = 1;
    GLuint specularNr = 1;

    shader.Bind();

    for ( u32 i = 0; i < _textures.size(); ++i )
    {
        std::stringstream ss;
        std::string number;

        TextureType type = _textures[ i ].type;

        if ( type == TextureType::Diffuse )
            ss << diffuseNr++;
        else if ( type == TextureType::Specular )
            ss << specularNr++;

        number = ss.str();

        shader.UpdateUniform( ( "material." + TextureTypeNames[ (u32)type ] + number ).c_str(), i );
        bind_texture( &_textures[ i ], i );
    }

    glActiveTexture( GL_TEXTURE0 );

    //Draw Mesh
    _vao.Bind();
    glDrawElements( GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0 );
    _vao.UnBind();
  }
}