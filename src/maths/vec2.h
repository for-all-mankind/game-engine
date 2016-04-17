#ifndef ICE_VEC2_H
#define ICE_VEC2_H

#include "../util/types.h"
#include "maths_util.h"

#include <iostream>

namespace Ice
{
  class Vec2
  {
  public:
    Vec2();
    Vec2( f32 x, f32 y );

    f32 Length  () const;
    f32 LengthSq() const;

    f32 Distance  ( const Vec2& other ) const;
    f32 DistanceSq( const Vec2& other ) const;

    f32 Dot( const Vec2& other ) const;

    Vec2& Normalise ();
    Vec2  Normalised() const;

    Vec2 operator+( const Vec2& r ) const;
    Vec2 operator-( const Vec2& r ) const;
    Vec2 operator*( f32 r ) const;
    Vec2 operator/( f32 r ) const;

    Vec2& operator+=( const Vec2& r );
    Vec2& operator-=( const Vec2& r );
    Vec2& operator*=( f32 r );
    Vec2& operator/=( f32 r );

    bool operator==( const Vec2& r ) const;
    bool operator!=( const Vec2& r ) const;

    friend std::ostream& operator<<( std::ostream& stream, const Vec2& vec );

  public:
    static const Vec2 Zero;
    static const Vec2 One;
    static const Vec2 UnitX;
    static const Vec2 UnitY;

    f32 X;
    f32 Y;
  };
}

#endif // ICE_VEC2_H