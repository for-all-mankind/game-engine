#ifndef ICE_RENDERER_H
#define ICE_RENDERER_H

#include "Types.hpp"
#include "NonCopy.hpp"
#include "Maths.hpp"
#include "RenderContext.hpp"

// temp
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

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