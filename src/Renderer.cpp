#include <Ice/Renderer.hpp>
#include <Ice/Window.hpp>
#include <Ice/Vertex.hpp>
#include <Ice/Maths.hpp>

namespace Ice
{
  Renderer::Renderer()
  {
    // Set the default clear colour.
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

    // Tell OpenGL which face to cull.
    glFrontFace( GL_CW    );
    glCullFace ( GL_FRONT );


    _texture = new Texture2D( "data/test/box.jpg" );
    _shader  = new Shader   ( "data/shaders/basic.vert",
                              "data/shaders/basic.frag" );

    _shader->RegisterUniform( "model"      );
    _shader->RegisterUniform( "view"       );
    _shader->RegisterUniform( "projection" );

    _shader->RegisterUniform( "light_colour" );
    _shader->RegisterUniform( "box_colour"   );

    Vertex vertices1[] = {
    //        Positions                         Colours                        Texture Coordinates
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },

      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },

      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },

      Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ 0.5f,  0.5f, -0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ 0.5f, -0.5f,  0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },

      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },

      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } }
    };

    Vertex vertices2[] = {
    //        Positions                         Colours                        Texture Coordinates
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },

      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },

      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },

      Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ 0.5f,  0.5f, -0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ 0.5f, -0.5f, -0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{ 0.5f, -0.5f,  0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ 0.5f,  0.5f,  0.5f, }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },

      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },

      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 0.0f } },
      Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 0.0f, 1.0f } }
    };


    // GLuint indices[] = {
    //   0, 1, 2, // Front
    //   3, 4, 5,

    //   4, 5, 0, // Right
    //   0, 5, 1,

    //   7, 6, 4, // Back
    //   4, 6, 5,

    //   3, 2, 7, // Left
    //   7, 2, 6,

    //   4, 0, 7, // Top
    //   7, 0, 3,

    //   1, 5, 2, // Bottom
    //   2, 5, 6,
    // };

    _cube_vao.Bind();

    _cube_vao.VBO().Bind();
    _cube_vao.VBO().BufferData( sizeof( vertices1 ), vertices1, GL_STATIC_DRAW );

    // _cube_vao.EBO().Bind();
    // _cube_vao.EBO().BufferData( sizeof( indices  ), indices , GL_STATIC_DRAW );

    _cube_vao.SetVAP( 0, VERTEX_SIZE_POSITION , GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_POSITION  );
    // _cube_vao.SetVAP( 1, VERTEX_SIZE_COLOUR   , GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_COLOUR    );
    _cube_vao.SetVAP( 2, VERTEX_SIZE_TEX_COORD, GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_TEX_COORD );
    _cube_vao.UnBind();

    _light_vao.Bind();


    _light_vao.Bind();

    _light_vao.VBO().Bind();
    _light_vao.VBO().BufferData( sizeof( vertices2 ), vertices2, GL_STATIC_DRAW );

    // _light_vao.EBO().Bind();
    // _light_vao.EBO().BufferData( sizeof( indices  ), indices , GL_STATIC_DRAW );

    _light_vao.SetVAP( 0, VERTEX_SIZE_POSITION , GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_POSITION  );
    // _light_vao.SetVAP( 1, VERTEX_SIZE_COLOUR   , GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_COLOUR    );
    // _light_vao.SetVAP( 2, VERTEX_SIZE_TEX_COORD, GL_FLOAT, GL_FALSE, VERTEX_SIZE, VERTEX_OFFSET_TEX_COORD );
    _light_vao.UnBind();

    _light_vao.Bind();



    _cube.SetTranslation( glm::vec3{ 1.0f, 1.0f, 0.0f } );
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

      glm::vec3 position = camera->Position();
      glm::vec3 up       = camera->Up();
      glm::vec3 forward  = camera->Forward();

      _view = glm::lookAt( position, position + forward, up );
    // }
    // else

    _shader->Bind();
    _shader->UpdateUniform( "model"     , _cube.GetTransform() );
    _shader->UpdateUniform( "view"      , _view                );
    _shader->UpdateUniform( "projection", context.projection   );

    _shader->UpdateUniform( "light_colour", glm::vec3( 1.0f, 1.0f, 1.0f ) );
    _shader->UpdateUniform( "box_colour"  , glm::vec3( 1.0f, 0.5f, 0.31f ) );
    _texture->Bind( GL_TEXTURE0 );

    _cube_vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
    _cube_vao.UnBind();
  }

  void Renderer::Clear()
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
}