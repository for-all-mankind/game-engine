#ifndef ICE_IMAGE_LOADER_H
#define ICE_IMAGE_LOADER_H

#include "Types.hpp"

namespace Ice
{
  enum class ImageFormat : u32
  {
    None           = 0,
    Greyscale      = 1,
    GreyscaleAlpha = 2,
    RGB            = 3,
    RGBA           = 4
  };

  /////////////////////////////////

  struct Image
  {
    ImageFormat format;

    u32 width;
    u32 height;
    u8* pixels;

    ~Image();
  };

  /////////////////////////////////

  Image load_image( const char* filename );
  Image load_image( u32 width, u32 height, ImageFormat format, const u8* pixels = nullptr );

  void flip_image_v( Image& image );
  void flip_image_h( Image& image );

  void rotate_image( Image& image );
}

#endif // ICE_IMAGE_LOADER_H