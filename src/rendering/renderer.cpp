#include "renderer.h"

#include "../core/window.h"

namespace Ice
{
  Renderer::Renderer()
  {
    // Set the default clear colour.
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

    // Tell OpenGL which face to cull.
    glFrontFace( GL_CW    );
    glCullFace ( GL_FRONT );


    _texture = new Texture( "res/test/box.jpg" );
    _shader  = new Shader ( "res/shaders/basic.vert",
                            "res/shaders/basic.frag" );

    _shader->RegisterUniform( "model"      );
    _shader->RegisterUniform( "view"       );
    _shader->RegisterUniform( "projection" );

    _view = Mat4::Translation( Vec3{ 0.0f, 0.0f, -5.0f } );

    GLfloat vertices[] = {
    // Positions          /**/ Colours           /**/ Texture Coordinates
       0.5f,  0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // Front Top Right
       0.5f, -0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // Front Bottom Right
      -0.5f, -0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // Front Bottom Left
      -0.5f,  0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, // Front Top Left
       0.5f,  0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // Back Top Right
       0.5f, -0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // Back Bottom Right
      -0.5f, -0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // Back Bottom Left
      -0.5f,  0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, // Back Top Left
    };

    GLuint indices[] = {
      0, 1, 3, // Front
      3, 1, 2,

      4, 5, 0, // Right
      0, 5, 1,

      7, 6, 4, // Back
      4, 6, 5,

      3, 2, 7, // Left
      7, 2, 6,

      4, 0, 7, // Top
      7, 0, 3,

      1, 5, 2, // Bottom
      2, 5, 6,
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
    context.wire_frame
      ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
      : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    context.has_depth
      ? glEnable ( GL_DEPTH_TEST )
      : glDisable( GL_DEPTH_TEST );

    f32 time  = static_cast<f32>( glfwGetTime() );
    f32 angle = time * 20.0f;

    _t.SetRotation( Vec3{ angle, angle, 0.0f } );

    _shader->Bind();
    _shader->UpdateUniform( "model"     , _t.GetTransform()  );
    _shader->UpdateUniform( "view"      , _view              );
    _shader->UpdateUniform( "projection", context.projection );
    _texture->Bind();

    _vao.Bind();
    glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
    _vao.UnBind();
  }

  void Renderer::Clear()
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
}