#include <Ice/Graphics/Renderer.hpp>
#include <Ice/Graphics/Vertex.hpp>
#include <Ice/System/Window.hpp>
#include <Ice/Maths/Maths.hpp>

namespace Ice
{
  Renderer::Renderer()
  {
    // Set the default clear colour.
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

    // Tell OpenGL which face to cull.
    // glFrontFace( GL_CW    );
    // glCullFace ( GL_FRONT );

    _texture = load_texture( "data/test/box.jpg" );

    _shader  = new Shader( "data/shaders/basic.vert",
                           "data/shaders/basic.frag" );

    _shader->RegisterUniform( "model"      );
    _shader->RegisterUniform( "view"       );
    _shader->RegisterUniform( "projection" );

    Vertex vertices[] = {
    //  Positions                Colours       Texture Coordinates
      { { +0.5f, +0.5f, +0.0f }, Colour_White, { 1.0f, 0.0f } },
      { { +0.5f, -0.5f, +0.0f }, Colour_Red  , { 1.0f, 1.0f } },
      { { -0.5f, -0.5f, +0.0f }, Colour_Green, { 0.0f, 1.0f } },
      { { -0.5f, +0.5f, +0.0f }, Colour_Blue , { 0.0f, 0.0f } },
    };

    GLuint indices[] = {
      0, 1, 3,
      3, 1, 2
    };

    _cube_vao.Bind();

    _cube_vao.VBO().Bind();
    _cube_vao.VBO().BufferData( sizeof( vertices ), vertices, GL_STATIC_DRAW );

    _cube_vao.EBO().Bind();
    _cube_vao.EBO().BufferData( sizeof( indices ), indices , GL_STATIC_DRAW );

    _cube_vao.SetVAP( 0, V_COMPONENTS_P, V_TYPE_P, V_NORMALISE_P, VERTEX_SIZE, V_OFFSET_P );
    _cube_vao.SetVAP( 1, V_COMPONENTS_C, V_TYPE_C, V_NORMALISE_C, VERTEX_SIZE, V_OFFSET_C );
    _cube_vao.SetVAP( 2, V_COMPONENTS_T, V_TYPE_T, V_NORMALISE_T, VERTEX_SIZE, V_OFFSET_T );
    _cube_vao.UnBind();

    _cube.SetTranslation( { 0.0f, 0.0f, 0.0f } );
    _cube.SetScale      ( { 1.0f, 1.0f, 1.0f } );
    // _cube.SetRotation   ( { 2.0f, 1.0f, 0.0f } );

    // _view = look_at( { 1.0f, 2.0f, 4.0f },
    //                  { 1.0f, 0.0f, 0.0f },
    //                  { 0.0f, 1.0f, 0.0f } );

    _view = translate( { 0.0f, 0.0f, 0.0f } );
  }

  Renderer::~Renderer()
  {
    delete _shader;
  }

  void Renderer::Render( const RenderContext& context )
  {
    context.wire_frame
      ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
      : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    context.has_depth
      ? glEnable ( GL_DEPTH_TEST )
      : glDisable( GL_DEPTH_TEST );

    _cube.SetTranslation( { sinf( glfwGetTime() ), cosf( glfwGetTime() ), 0.0f } );
    // _cube.SetScale      ( { sinf( glfwGetTime() ), cosf( glfwGetTime() ), 0.0f } );

    // _view = translate( { sinf( glfwGetTime() ), cosf( glfwGetTime() ), -2.0f } );

    _shader->Bind();
    _shader->UpdateUniform( "model"     , _cube.GetTransform() );
    _shader->UpdateUniform( "view"      , _view                );
    _shader->UpdateUniform( "projection", context.projection   );

    bind_texture( &_texture, 0 );

    _cube_vao.Bind();
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    _cube_vao.UnBind();
  }

  void Renderer::Clear()
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
}