#ifndef ICE_GRAPHICS_COLOUR_HPP
#define ICE_GRAPHICS_COLOUR_HPP

#include <Ice/Common/Types.hpp>

namespace Ice
{

  union Colour
  {
    Colour( u8 r, u8 g, u8 b, u8 a )
      : bytes{ r, g, b, a }
    {}

    u8 bytes [ 4 ];

    struct { u8 r, g, b, a; };
  };

  const Colour Colour_White  = Colour{ 255, 255, 255, 255 };
  const Colour Colour_Black  = Colour{ 0  , 0  , 0  , 255 };
  const Colour Colour_Red    = Colour{ 255, 0  , 0  , 255 };
  const Colour Colour_Green  = Colour{ 0  , 255, 0  , 255 };
  const Colour Colour_Blue   = Colour{ 0  , 0  , 255, 255 };
  const Colour Colour_Purple = Colour{ 0  , 255, 255, 255 };
  const Colour Colour_Cyan   = Colour{ 255, 0  , 255, 255 };
  const Colour Colour_Yellow = Colour{ 255, 255, 0  , 255 };

}

#endif // ICE_GRAPHICS_COLOUR_HPP