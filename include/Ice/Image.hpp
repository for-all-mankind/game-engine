#ifndef ICE_IMAGE_LOADER_H
#define ICE_IMAGE_LOADER_H

#include <Ice/Common/Types.hpp>

namespace Ice
{
  enum ImageFormat
  {
    Format_Greyscale      = 1,
    Format_GreyscaleAlpha = 2,
    Format_RGB            = 3,
    Format_RGBA           = 4
  };

  /////////////////////////////////

  enum ImageRotate
  {
    Rotate_90  = 90,
    Rotate_180 = 90,
    Rotate_270 = 90
  };

  /////////////////////////////////

  struct Rect
  {
    u32 x;
    u32 y;
    u32 w;
    u32 h;
  };

  /////////////////////////////////

  class Image
  {
  public:
    Image();
    Image( u32 width, u32 height, ImageFormat format, const u8* pixels = nullptr );
    Image( const Image& image );

    Image& operator=( const Image& image );

    ~Image();

    bool Load( const char* filename );
    bool Load( u32 width, u32 height, ImageFormat format, const u8* pixels = nullptr );

    inline u32 Width () const { return _width;  }
    inline u32 Height() const { return _height; }
    inline u8* Pixels() const { return _pixels; }

    inline ImageFormat Format() const { return _format; }

    u8*  GetPixel( u32 x, u32 y );
    void SetPixel( u32 x, u32 y, const u8* pixel );

    void Flip  ( bool vertical = false, bool horizontal = false );
    void Rotate( ImageRotate amount );

    void CopyRect( const Image& src, Rect src_rect, u32 dest_x, u32 dest_y );

  private:
    ImageFormat _format;
    u32 _width;
    u32 _height;
    u8* _pixels;

  };
}

#endif // ICE_IMAGE_LOADER_H