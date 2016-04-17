#ifndef ICE_VEC4_H
#define ICE_VEC4_H

#include "../util/types.h"
#include "maths_util.h"

#include <iostream>

namespace Ice
{
  class Vec4
  {
  public:
    Vec4();
    Vec4( f32 x, f32 y, f32 z, f32 w );

    f32 Length  () const;
    f32 LengthSq() const;

    f32 Distance  ( const Vec4& other ) const;
    f32 DistanceSq( const Vec4& other ) const;

    f32 Dot( const Vec4& other ) const;

    Vec4& Normalise ();
    Vec4  Normalised() const;

    Vec4 operator+( const Vec4& r ) const;
    Vec4 operator-( const Vec4& r ) const;
    Vec4 operator*( f32 r ) const;
    Vec4 operator/( f32 r ) const;

    Vec4& operator+=( const Vec4& r );
    Vec4& operator-=( const Vec4& r );
    Vec4& operator*=( f32 r );
    Vec4& operator/=( f32 r );

    bool operator==( const Vec4& r ) const;
    bool operator!=( const Vec4& r ) const;

    friend std::ostream& operator<<( std::ostream& stream, const Vec4& vec );

  public:
    static const Vec4 Zero;
    static const Vec4 One;
    static const Vec4 UnitX;
    static const Vec4 UnitY;
    static const Vec4 UnitZ;
    static const Vec4 UnitW;

    f32 X;
    f32 Y;
    f32 Z;
    f32 W;
  };
}

#endif // ICE_VEC4_H