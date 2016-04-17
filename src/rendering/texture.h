#ifndef ICE_TEXTURE_H
#define ICE_TEXTURE_H

#include <GL/glew.h>
#include <string>

namespace Ice
{
  class Texture
  {
  public:
    Texture( const std::string& filename );
    ~Texture();

    void Bind();
    void UnBind();

  private:
    GLuint _handle;
  };
}

#endif // ICE_TEXTURE_H