#ifndef ICE_RENDERER_H
#define ICE_RENDERER_H

#include "../scene/node.h"
#include "../core/camera.h"
#include "render_context.h"

// temp
#include "buffers/buffers.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

namespace Ice
{
  class Renderer
  {
  public:
    Renderer();
    ~Renderer();

    void Render( const NodeRef& node, const RenderContext& context, Camera* camera );
    void Clear();

  private:
    Shader* _shader;
    glm::mat4    _view;


    // Temp
    Texture* _texture;
    GLvao _vao;
    Transform _t;
  };
}

#endif // ICE_RENDERER_H