#include "Quaternion.hpp"

namespace Ice
{
  Quaternion::Quaternion()
    : w( 0.0f )
    , v( 0.0f )
  {}

  Quaternion::Quaternion( f32 a, const Vec3& n )
  {
    f32 s = sinf( a / 2.0f );
        w = cosf( a / 2.0f );
        v = n * s;
  }

  Quaternion conjugate( const Quaternion& q )
  {
    Quaternion result;

    result.w =  q.w;
    result.v = -q.v;

    return result;
  }

  Quaternion slerp( const Quaternion& origin,
                    const Quaternion& target,
                    f32 amount )
  {
    Quaternion  result;
    Quaternion _target = target;

    f32 flCosOmega = origin.w * _target.w + dot( _target.v, origin.v );

    if ( flCosOmega < 0 )
    {
      // Avoid going the long way around.
      _target.w   = -_target.w;
      _target.v   = -_target.v;
       flCosOmega = -flCosOmega;
    }

    f32 k0;
    f32 k1;

    if (flCosOmega > 0.9999f)
    {
      // Very close, use a linear interpolation.
      k0 = 1 - amount;
      k1 =     amount;
    }
    else
    {
      // Trig identity, sin^2 + cos^2 = 1
      f32 flSinOmega = sqrt( 1 - flCosOmega * flCosOmega );

      // Compute the angle omega
      f32 flOmega = atan2( flSinOmega, flCosOmega );
      f32 flOneOverSinOmega = 1 / flSinOmega;

      k0 = sin( ( 1 - amount ) * flOmega ) * flOneOverSinOmega;
      k1 = sin( amount*flOmega ) * flOneOverSinOmega;
    }

    // Interpolate
    result.w = origin.w * k0 + _target.w * k1;
    result.v = origin.v * k0 + _target.v * k1;

    return result;
  }
}