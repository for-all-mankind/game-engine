#ifndef ICE_VEC3_H
#define ICE_VEC3_H

#include "../util/types.h"
#include "maths_util.h"

#include <iostream>

namespace Ice
{
  class Vec3
  {
  public:
    Vec3();
    Vec3( f32 x, f32 y, f32 z );

    f32 Length  () const;
    f32 LengthSq() const;

    f32 Distance  ( const Vec3& other ) const;
    f32 DistanceSq( const Vec3& other ) const;

    f32  Dot  ( const Vec3& other ) const;
    Vec3 Cross( const Vec3& other ) const;

    Vec3& Normalise ();
    Vec3  Normalised() const;

    Vec3 operator+( const Vec3& r ) const;
    Vec3 operator-( const Vec3& r ) const;
    Vec3 operator*( f32 r ) const;
    Vec3 operator/( f32 r ) const;

    Vec3& operator+=( const Vec3& r );
    Vec3& operator-=( const Vec3& r );
    Vec3& operator*=( f32 r );
    Vec3& operator/=( f32 r );

    bool operator==( const Vec3& r ) const;
    bool operator!=( const Vec3& r ) const;

    friend std::ostream& operator<<( std::ostream& stream, const Vec3& vec );

  public:
    static const Vec3 Zero;
    static const Vec3 One;
    static const Vec3 UnitX;
    static const Vec3 UnitY;
    static const Vec3 UnitZ;

    f32 X;
    f32 Y;
    f32 Z;
  };
}

#endif // ICE_VEC3_H