#include "maths_util.h"

namespace Ice
{
  f32 to_radians( f32 degrees )
  {
    return degrees * ( M_PI / 180.0f );
  }

  f32 to_degrees( f32 radians )
  {
    return radians / ( M_PI / 180.0f );
  }
}