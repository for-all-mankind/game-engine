#include <Ice/Common/Types.hpp>
#include <Ice/Common/Common.hpp>
#include <Ice/Texture2D.hpp>

namespace Ice
{

  static GLenum get_internal_format( ImageFormat format, bool srgb )
  {
    switch( format )
    {
      case Format_Greyscale:
        return GL_LUMINANCE;
      case Format_GreyscaleAlpha:
        return GL_LUMINANCE_ALPHA;
      case Format_RGB:
        return ( srgb ? GL_SRGB  : GL_RGB  );
      case Format_RGBA:
        return GL_RGBA;//( srgb ? GL_SRGBA : GL_RGBA );
      default:
        throw std::runtime_error( "Invalid image format!" );
    }
  }

  /////////////////////////////////

  Texture2D::Texture2D( const Image& image,
                        GLint min_filter,
                        GLint mag_filter,
                        GLint wrap_mode )
    : _handle      ( 0 )
    , _pixel_width ( 0 )
    , _pixel_height( 0 )
  {
    if ( !Load( image, min_filter, mag_filter, wrap_mode ) )
      throw std::runtime_error( "Could not create texture" );
  }

  Texture2D::Texture2D( const char* filename,
                        GLint min_filter,
                        GLint mag_filter,
                        GLint wrap_mode )
    : _handle      ( 0 )
    , _pixel_width ( 0 )
    , _pixel_height( 0 )
  {
    if ( !Load( filename, min_filter, mag_filter, wrap_mode ) )
      throw std::runtime_error( "Could not create texture" );
  }

  Texture2D::~Texture2D()
  {
    glDeleteTextures( 1, &_handle );
  }

  bool Texture2D::Load( const Image& image,
                        GLint min_filter,
                        GLint mag_filter,
                        GLint wrap_mode )
  {
    _pixel_width  = image.Width();
    _pixel_height = image.Height();

    glGenTextures( 1, &_handle );
    glBindTexture( GL_TEXTURE_2D, _handle );

    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , wrap_mode  );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , wrap_mode  );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter );
    glGenerateMipmap( GL_TEXTURE_2D );

    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  get_internal_format( image.Format(), true ),
                  static_cast<GLsizei>( _pixel_width  ),
                  static_cast<GLsizei>( _pixel_height ),
                  0,
                  get_internal_format( image.Format(), false ),
                  GL_UNSIGNED_BYTE,
                  image.Pixels() );

    glBindTexture( GL_TEXTURE_2D, 0 );

    return true;
  }

  bool Texture2D::Load( const char* filename,
                        GLint min_filter,
                        GLint mag_filter,
                        GLint wrap_mode )
  {
    Image image;

    if ( !image.Load( filename ) )
      return false;

    image.Flip( true );

    return Load( image, min_filter, mag_filter, wrap_mode );
  }

  void Texture2D::Bind( GLuint position )
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
    glBindTexture( GL_TEXTURE_2D, ( _handle ? _handle : 0 ) );
    glDisable( GL_TEXTURE_2D );
  }

  void Texture2D::UnBind()
  {
    glBindTexture( GL_TEXTURE_2D, 0 );
  }
}