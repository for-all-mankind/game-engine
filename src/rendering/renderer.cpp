#include "renderer.h"

namespace Ice
{
  Renderer::Renderer()
  {
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

    // glEnable( GL_DEPTH_TEST );

    _texture = new Texture( "res/test/download.jpg" );
    _shader  = new Shader ( "res/shaders/basic.vert",
                            "res/shaders/basic.frag" );

    _shader->RegisterUniform( "transform" );

    GLfloat vertices[] = {
    // Positions          /**/ Colours           /**/ Texture Coordinates
       0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // Top Right
       0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // Bottom Right
      -0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // Bottom Left
      -0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, // Top Left
    };

    GLuint indices[] = {
      0, 1, 3, // Front
      3, 1, 2
    };

    _vao.Bind();

    _vao.VBO().Bind();
    _vao.VBO().BufferData( sizeof( vertices ), vertices, GL_STATIC_DRAW );

    _vao.EBO().Bind();
    _vao.EBO().BufferData( sizeof( indices  ), indices , GL_STATIC_DRAW );

    _vao.SetVAP( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), (GLvoid*)( 0 * sizeof( GLfloat ) ) );
    _vao.SetVAP( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), (GLvoid*)( 3 * sizeof( GLfloat ) ) );
    _vao.SetVAP( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), (GLvoid*)( 6 * sizeof( GLfloat ) ) );
    _vao.UnBind();
  }

  Renderer::~Renderer()
  {
    delete _texture;
    delete _shader;
  }

  #include <GLFW/glfw3.h>

  void Renderer::Render( const NodeRef& node, const RenderContext& context )
  {
    // wire_frame mode on
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // wire_frame mode off
    // glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    f32 time = static_cast<f32>( glfwGetTime() );

    _t.SetRotation( time * 2.0f, Vec3{ 0.0f, 0.0f, 1.0f } );

    _t.SetTranslation( Vec3{ sinf( time ) / 2.0f, cosf( time ) / 2.0f, 0.0f } );

    _shader->Bind();
    _shader->UpdateUniform( "transform", _t.GetModel() );
    _texture->Bind();

    _vao.Bind();
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    _vao.UnBind();
  }

  void Renderer::Clear()
  {
    // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClear( GL_COLOR_BUFFER_BIT );
  }
}