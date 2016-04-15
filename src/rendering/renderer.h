#ifndef ICE_RENDERER_H
#define ICE_RENDERER_H

#include "../scene/node.h"
#include "render_context.h"

namespace Ice
{
  class Renderer
  {
  public:
    Renderer();
    ~Renderer();

    void Render( const NodeRef& node, const RenderContext& context );

    void Clear();

  private:

  };
}

#endif // ICE_RENDERER_H