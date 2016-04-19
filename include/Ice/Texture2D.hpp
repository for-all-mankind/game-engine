#ifndef ICE_TEXTURE_H
#define ICE_TEXTURE_H

#include <Ice/Common/Types.hpp>
#include <Ice/Common/NonCopy.hpp>
#include <Ice/Common/OpenGL.hpp>
#include <Ice/Image.hpp>

namespace Ice
{
  class Texture2D : public Common::NonCopyable
  {
  public:
    Texture2D( const Image& image,
               GLint min_filter = GL_LINEAR_MIPMAP_LINEAR,
               GLint mag_filter = GL_LINEAR,
               GLint wrap_mode  = GL_REPEAT );
    Texture2D( const char* filename,
               GLint min_filter = GL_LINEAR_MIPMAP_LINEAR,
               GLint mag_filter = GL_LINEAR,
               GLint wrap_mode  = GL_REPEAT );

    virtual ~Texture2D();

    bool Load( const Image& image,
              GLint min_filter = GL_LINEAR_MIPMAP_LINEAR,
              GLint mag_filter = GL_LINEAR,
              GLint wrap_mode  = GL_REPEAT );
    bool Load( const char* filename,
              GLint min_filter = GL_LINEAR_MIPMAP_LINEAR,
              GLint mag_filter = GL_LINEAR,
              GLint wrap_mode  = GL_REPEAT );

    void Bind( GLuint position );
    void UnBind();

    inline GLuint Handle() const { return _handle; }

    inline GLuint Width () const { return _pixel_width;  }
    inline GLuint Height() const { return _pixel_height; }

  private:
    GLuint _handle;

    GLuint _pixel_width;
    GLuint _pixel_height;
  };
}

#endif // ICE_TEXTURE_H