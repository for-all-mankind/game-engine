#include <Ice/Common/Common.hpp>
#include <Ice/Image.hpp>

#define STBI_FAILURE_USERMSG
#include <Ice/stb_image.h>

#include <string.h>

namespace Ice
{
  Image::Image()
    : _format( (ImageFormat)0 )
    , _width ( 0 )
    , _height( 0 )
    , _pixels( nullptr )
  {

  }

  Image::Image( u32 width, u32 height, ImageFormat format, const u8* pixels )
  {
    Load( width, height, format, pixels );
  }

  Image::Image( const Image& image )
    : _format( (ImageFormat)0 )
    , _width ( 0 )
    , _height( 0 )
    , _pixels( nullptr )
  {
    Load( image._width,
          image._height,
          image._format,
          image._pixels );
  }

  Image& Image::operator=( const Image& image )
  {
    Load( image._width,
          image._height,
          image._format,
          image._pixels );

    return *this;
  }

  Image::~Image()
  {
    if ( _pixels != nullptr )
      delete _pixels;
  }

  bool Image::Load( const char* filename )
  {
    i32 width;
    i32 height;
    i32 format;

    // Using NULL because stbi_load takes an integer and nullptr
    // has type nullptr_t.
    u8* pixels = stbi_load( filename, &width, &height, &format, NULL );

    if ( !pixels )
    {
      std::cerr << stbi_failure_reason() << std::endl;
      return false;
    }

    Load( width, height, (ImageFormat)format, pixels );

    stbi_image_free( pixels );

    if ( _pixels )
      return true;

    return false;
  }

  bool Image::Load( u32 width, u32 height, ImageFormat format, const u8* pixels )
  {
    if ( width == 0 )
    {
      std::cerr << "Image width can't be zero!" << std::endl;
      return false;
    }
    if ( height == 0 )
    {
      std::cerr << "Image height can't be zero!" << std::endl;
      return false;
    }
    if ( format <= Format_Greyscale || format > Format_RGBA )
    {
      std::cerr << "Invalid format!" << std::endl;
      return false;
    }

    _width  = width;
    _height = height;
    _format = format;

    size_t image_size = width * height * format;

    if ( _pixels )
      delete[] _pixels;

    _pixels = new u8[ image_size ];

    if ( pixels != nullptr )
      memcpy( _pixels, pixels, image_size );

    return true;
  }

  u8* Image::GetPixel( u32 x, u32 y )
  {
    if ( x >= _width || y >= _height )
      return nullptr;

    return _pixels + ( x + y * _width ) * _format;
  }

  void Image::SetPixel( u32 x, u32 y, const u8* pixel )
  {
    u8* got_pixel = GetPixel( x, y );

    memcpy( got_pixel, pixel, _format );
  }

  void Image::Flip( bool vertical, bool horizontal )
  {
    if ( !vertical && !horizontal )
      return;

    if ( vertical )
    {
      size_t pitch      = _width * _format;
      u32    half_rows  = _height / 2;
      u8*    row_buffer = new u8[ pitch ];

      for ( u32 i = 0; i < half_rows; ++i )
      {
        u8* row = _pixels + ( i                   * _width ) * _format;
        u8* opp = _pixels + ( ( _height - i - 1 ) * _width ) * _format;

        memcpy( row_buffer, row       , pitch );
        memcpy( row       , opp       , pitch );
        memcpy( opp       , row_buffer, pitch );
      }

      delete[] row_buffer;
    }

    if ( horizontal )
    {
      size_t pitch      = _width * _format / 2;
      u32    half_width = _width / 2;
      u8*    row_buffer = new u8[ pitch ];

      for ( u32 i = 0; i < _height; ++i )
      {
        u8* row = _pixels + ( i * half_width              ) * _format;
        u8* opp = _pixels + ( i * half_width + half_width ) * _format;

        memcpy( row_buffer, row       , pitch );
        memcpy( row       , opp       , pitch );
        memcpy( opp       , row_buffer, pitch );
      }

      delete[] row_buffer;
    }
  }

  void Image::Rotate( ImageRotate amount )
  {
    std::cerr << "Warning: Image::Rotate(): Not yet implemented!" << std::endl;
  }

  void Image::CopyRect( const Image& src, Rect src_rect, u32 dest_x, u32 dest_y )
  {
    std::cerr << "Warning: Image::CopyRect(): Not yet implemented!" << std::endl;
  }
}