#include "texture.h"
#include "../util/stb_image.h"
#include "../util/types.h"

namespace Ice
{
  Texture::Texture( const std::string& filename )
  {
    i32 width;
    i32 height;

    i32 component_count;

    unsigned char* image_data = stbi_load( filename.c_str(), &width, &height, &component_count, STBI_rgb );

    if ( image_data == nullptr )
      throw( "Failed to load texture: " + filename );

    glGenTextures( 1, &_handle );
    glBindTexture( GL_TEXTURE_2D, _handle );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data );
    glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, 0 );

    stbi_image_free( image_data );
  }

  Texture::~Texture()
  {
    glDeleteTextures( 1, &_handle );
  }

  void Texture::Bind()
  {
    glBindTexture( GL_TEXTURE_2D, _handle );
  }

  void Texture::UnBind()
  {
    glBindTexture( GL_TEXTURE_2D, 0 );
  }
}