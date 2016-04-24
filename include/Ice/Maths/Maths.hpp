#ifndef ICE_MATHS_DEFINES_H
#define ICE_MATHS_DEFINES_H

#include <Ice/Maths/Vec2.hpp>
#include <Ice/Maths/Vec3.hpp>
#include <Ice/Maths/Vec4.hpp>
#include <Ice/Maths/Mat4.hpp>
#include <Ice/Maths/Quaternion.hpp>

namespace Ice
{
  struct Constants
  {
    static constexpr f32 Pi  = 3.14159265359;
    static constexpr f32 Tau = 6.28318530718;
  };
}

#endif // ICE_MATHS_DEFINES_H