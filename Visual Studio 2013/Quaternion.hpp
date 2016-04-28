#ifndef ICE_MATHS_QUATERNION_HPP
#define ICE_MATHS_QUATERNION_HPP

#include "Types.hpp"
#include "Vec3.hpp"

namespace Ice
{
  struct Quaternion
  {
    Quaternion();
    Quaternion( f32 a, const Vec3& n );

    inline Quaternion operator*( const Quaternion& r ) const
    {
      Quaternion result;

      result.w = w * r.w - dot( v, r.v );
      result.v = v * r.w + r.v * w + cross( v, r.v );

      return result;
    };

    inline Vec3 operator*( const Vec3& r ) const
    {
      Vec3 t = cross( v, r );

      return r + t * ( 2 * w ) + cross( v, t ) * 2;
    };

    f32  w;
    Vec3 v;
  };

  /////////////////////////////////

  Quaternion conjugate( const Quaternion& q );
  Quaternion slerp    ( const Quaternion& origin,
                        const Quaternion& target,
                        f32 amount );
}

#endif // ICE_MATHS_QUATERNION_HPP