#include "renderer.h"

#include <GL/glew.h>

namespace Ice
{
  Renderer::Renderer()
  {
    glClearColor( 0.0f, 0.05f, 0.15f, 1.0f );
  }

  Renderer::~Renderer()
  {

  }

  void Renderer::Render( const NodeRef& node, const RenderContext& context )
  {

  }

  void Renderer::Clear()
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
}