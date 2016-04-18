#ifndef ICE_RENDERER_H
#define ICE_RENDERER_H

#include "../scene/node.h"
#include "../maths/maths.h"
#include "buffers/buffers.h"
#include "render_context.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <GL/glew.h>

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
    Texture* _texture;
    Shader*  _shader;

    Mat4 _view;

    GLvao _vao;
    Transform _t;
  };
}

#endif // ICE_RENDERER_H