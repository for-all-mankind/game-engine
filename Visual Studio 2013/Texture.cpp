#include "Types.hpp"
#include "Common.hpp"
#include "Texture.hpp"

namespace Ice
{

  static GLenum get_internal_format( ImageFormat format, bool srgb )
  {
    switch( format )
    {
      case ImageFormat::Greyscale:
        return GL_LUMINANCE;
      case ImageFormat::GreyscaleAlpha:
        return GL_LUMINANCE_ALPHA;
      case ImageFormat::RGB:
        return ( srgb ? GL_SRGB: GL_RGB );
      case ImageFormat::RGBA:
        return ( srgb ? GL_SRGB_ALPHA : GL_RGBA );

      case ImageFormat::None:
      default:
        throw std::runtime_error( "Invalid image format!" );
    }
  }

  /////////////////////////////////

  Texture::~Texture()
  {
    glDeleteTextures( 1, &handle );
  }

  /////////////////////////////////

  Texture load_texture( const Image&  image,
                        TextureType   type,
                        TextureFilter min_filter,
                        TextureFilter mag_filter,
                        TextureWrapMode wrap_mode )
  {
    if ( image.format == ImageFormat::None )
      throw std::runtime_error( "Invalid image format" );

    Texture texture{ 0, image.width, image.height, type };

    glGenTextures( 1, &texture.handle );
    glBindTexture( GL_TEXTURE_2D, texture.handle );

    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , (i32)wrap_mode  );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , (i32)wrap_mode  );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (i32)min_filter );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (i32)mag_filter );
    glGenerateMipmap( GL_TEXTURE_2D );

    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  get_internal_format ( image.format, true ),
                  static_cast<GLsizei>( image.width  ),
                  static_cast<GLsizei>( image.height ),
                  0,
                  get_internal_format( image.format, false ),
                  GL_UNSIGNED_BYTE,
                  image.pixels );

    glBindTexture( GL_TEXTURE_2D, 0 );

    return texture;
  }

  Texture load_texture( const char*   filename,
                        TextureType   type,
                        TextureFilter min_filter,
                        TextureFilter mag_filter,
                        TextureWrapMode wrap_mode )
  {
    Image image = load_image( filename );

    // flip_image_v( image );

    return load_texture( image, type, min_filter, mag_filter, wrap_mode );
  }

  void bind_texture( const Texture* texture, u32 position )
  {
    if ( position > 31 )
    {
      std::cerr << "Textures can only be bound to position [ 0 .. 31 ]" << std::endl;
      std::cerr << "Using position 31." << std::endl;
      position = 31;
    }

    glActiveTexture      ( GL_TEXTURE0 + position );
    glClientActiveTexture( GL_TEXTURE0 + position );

    glEnable( GL_TEXTURE_2D );

    if ( texture && texture->handle )
      glBindTexture( GL_TEXTURE_2D, texture->handle );
    else
      glBindTexture( GL_TEXTURE_2D, 0 );
  }
}