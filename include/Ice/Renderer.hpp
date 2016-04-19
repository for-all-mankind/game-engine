#ifndef ICE_RENDERER_H
#define ICE_RENDERER_H

#include <Ice/Common/Types.hpp>
#include <Ice/Common/NonCopy.hpp>
#include <Ice/Maths.hpp>
#include <Ice/Node.hpp>
#include <Ice/Camera.hpp>
#include <Ice/RenderContext.hpp>

// temp
#include <Ice/Buffers.hpp>
#include <Ice/Shader.hpp>
#include <Ice/Texture2D.hpp>
#include <Ice/Transform.hpp>

#include <GL/glew.h>

namespace Ice
{
  class Renderer : public Common::NonCopyable
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
    Texture2D* _texture;
    GLvao      _cube_vao;
    Transform  _cube;
    GLvao      _light_vao;
    Transform  _light;
  };
}

#endif // ICE_RENDERER_H