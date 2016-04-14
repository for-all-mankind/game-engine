#ifndef ICE_MATHS_UTIL_H
#define ICE_MATHS_UTIL_H

#include "../util/types.h"

#define  _USE_MATH_DEFINES
#include <cmath>

namespace Ice
{
  f32 to_radians( f32 degrees );
  f32 to_degrees( f32 radians );
}



#endif // ICE_MATHS_UTIL_H