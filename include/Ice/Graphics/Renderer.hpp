#ifndef ICE_RENDERER_H
#define ICE_RENDERER_H

#include <Ice/Common/Types.hpp>
#include <Ice/Common/NonCopy.hpp>
#include <Ice/Maths/Maths.hpp>
#include <Ice/Graphics/RenderContext.hpp>

// temp
#include <Ice/Graphics/Mesh.hpp>
#include <Ice/Graphics/Shader.hpp>
#include <Ice/Graphics/Texture.hpp>
#include <Ice/Transform.hpp>

#include <GL/glew.h>

namespace Ice
{
  class Renderer : public Common::NonCopyable
  {
  public:
    Renderer();
    ~Renderer();

    void Render( const RenderContext& context );
    void Clear();

  private:
    Shader* _shader;
    Mat4    _view;


    // Temp
    Texture   _texture;
    Mesh      _cube_mesh;
    Transform _cube;
  };
}

#endif // ICE_RENDERER_H