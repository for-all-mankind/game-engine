#include <Ice/Common/Common.hpp>
#include <Ice/Graphics/Image.hpp>

#define STBI_FAILURE_USERMSG
#include <Ice/Graphics/stb_image.h>

#include <string.h>

namespace Ice
{
  Image::~Image()
  {
    if ( pixels != nullptr )
      delete pixels;
  }

  Image load_image( const char* filename )
  {
    i32 width;
    i32 height;
    i32 format;

    // Using NULL because stbi_load takes an integer and nullptr
    // has type nullptr_t.
    u8* pixels = stbi_load( filename, &width, &height, &format, 0 );
    defer( stbi_image_free( pixels ) );

    if ( !pixels )
      throw std::runtime_error( stbi_failure_reason() );

    return load_image( width, height, (ImageFormat)format, pixels );
  }

  Image load_image( u32 width, u32 height, ImageFormat format, const u8* pixels )
  {
    if ( width == 0 )
      throw std::runtime_error( "Image width can't be zero!" );

    if ( height == 0 )
      throw std::runtime_error( "Image height can't be zero!" );

    Image img;

    img.width  = width;
    img.height = height;
    img.format = format;

    usize image_size = width * height * (u32)format;

    img.pixels = new u8[ image_size ];

    if ( pixels != nullptr )
      memcpy( img.pixels, pixels, image_size );

    return img;
  }

  void flip_image_v( Image& img )
  {
    usize pitch      = img.width * (u32)img.format;
    u32   half_rows  = img.height / 2;
    u8*   temp = new u8[ pitch ];

    defer( delete[] temp );

    for ( u32 i = 0; i < half_rows; ++i )
    {
      u8* row = img.pixels + ( i                      * img.width ) * (u32)img.format;
      u8* opp = img.pixels + ( ( img.height - i - 1 ) * img.width ) * (u32)img.format;

      memcpy( temp, row , pitch );
      memcpy( row , opp , pitch );
      memcpy( opp , temp, pitch );
    }
  }

  void flip_image_h( Image& img )
  {
    std::cerr << "Warning: Image::FlipH(): Not yet implemented!" << std::endl;
    return;

    size_t pitch      = img.width * (u32)img.format / 2;
    u32    half_width = img.width / 2;
    u8*    temp = new u8[ pitch ];

    defer( delete[] temp );

    for ( u32 i = 0; i < img.height; ++i )
    {
      u8* row = img.pixels + ( i * half_width              ) * (u32)img.format;
      u8* opp = img.pixels + ( i * half_width + half_width ) * (u32)img.format;

      memcpy( temp, row , pitch );
      memcpy( row , opp , pitch );
      memcpy( opp , temp, pitch );
    }
  }

  void rotate_image( Image& img )
  {
    std::cerr << "Warning: Image::Rotate(): Not yet implemented!" << std::endl;
  }
}