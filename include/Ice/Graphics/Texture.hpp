#ifndef ICE_TEXTURE_H
#define ICE_TEXTURE_H

#include <Ice/Common/Types.hpp>
#include <Ice/Common/NonCopy.hpp>
#include <Ice/Common/OpenGL.hpp>
#include <Ice/Graphics/Image.hpp>

namespace Ice
{
  enum class TextureFilter : i32
  {
    LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR,
    LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
    NearestMipmapNearser = GL_NEAREST_MIPMAP_NEAREST,

    Linear  = GL_LINEAR,
    Nearest = GL_NEAREST
  };

  /////////////////////////////////

  enum class TextureWrapMode : i32
  {
    Clamp          = GL_CLAMP,
    Repeat         = GL_REPEAT,
    ClampToEdge    = GL_CLAMP_TO_EDGE,
    ClampToBorder  = GL_CLAMP_TO_BORDER,
    MirroredRepeat = GL_MIRRORED_REPEAT
  };

  /////////////////////////////////

  enum class TextureType : i32
  {
    Diffuse,
    Specular,
  };

  // TODO:
  // Find a better way to do this... Maybe macros.
  // This one isn't too bad because it's only a small
  // enum, but this requirement may come up again.

  const std::string TextureTypeNames[] = {
    "texture_diffuse",
    "texture_specular"
  };

  /////////////////////////////////

  struct Texture
  {
    u32 handle;
    u32 width;
    u32 height;

    TextureType type;

    ~Texture();
  };

  /////////////////////////////////

  Texture load_texture( const Image&    image,
                        TextureType     type,
                        TextureFilter   min_filter = TextureFilter::LinearMipmapLinear,
                        TextureFilter   mag_filter = TextureFilter::Linear,
                        TextureWrapMode wrap_mode  = TextureWrapMode::Repeat );

  Texture load_texture( const char*     filename,
                        TextureType     type,
                        TextureFilter   min_filter = TextureFilter::LinearMipmapLinear,
                        TextureFilter   mag_filter = TextureFilter::Linear,
                        TextureWrapMode wrap_mode  = TextureWrapMode::Repeat );

  void bind_texture( const Texture* texture, u32 position );
}

#endif // ICE_TEXTURE_H