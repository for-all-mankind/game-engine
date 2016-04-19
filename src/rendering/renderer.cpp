#include "renderer.h"

#include "../core/window.h"
#include "vertex.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    _view = glm::translate( _view, glm::vec3( 0.0f, 0.0f, -5.0f ) );

    Vertex vertices[] = {
    //        Positions                    Colours                   Texture Coordinates
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } }, // Front Top Right
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } }, // Front Bottom Right
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } }, // Front Bottom Left
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } }, // Front Top Left
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } }, // Back Top Right
      Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } }, // Back Bottom Right
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } }, // Back Bottom Left
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } }, // Back Top Left
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

    _vao.SetVAP( 0, VERTEX_SIZE_POSITION , GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_POSITION  );
    _vao.SetVAP( 1, VERTEX_SIZE_COLOUR   , GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_COLOUR    );
    _vao.SetVAP( 2, VERTEX_SIZE_TEX_COORD, GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_TEX_COORD );
    _vao.UnBind();
  }

  Renderer::~Renderer()
  {
    delete _texture;
    delete _shader;
  }

  #include <GLFW/glfw3.h>

  void Renderer::Render( const NodeRef& node, const RenderContext& context, Camera* camera )
  {
    context.wire_frame
      ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
      : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    context.has_depth
      ? glEnable ( GL_DEPTH_TEST )
      : glDisable( GL_DEPTH_TEST );

    f32 time  = static_cast<f32>( glfwGetTime() );
    f32 angle = time;

    // if ( camera != nullptr )
    // {
    //   camera->Move( Vec3_UnitX, -time / 100.0f );
    //   camera->Rotate( 0.0f, -time / 100.0f );

    //   glm::vec3 position = camera->Position();
    //   glm::vec3 up       = camera->Up();
    //   glm::vec3 forward  = camera->Forward();

    //   _view = glm::lookAt( position, position + forward, up );
    // }
    // else

    _t.SetRotation( angle, glm::vec3{ 1.0f, 1.0f, 0.0f } );

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