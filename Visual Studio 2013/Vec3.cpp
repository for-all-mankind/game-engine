#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace Ice
{
  Vec3::Vec3()
    : x( 0 )
    , y( 0 )
    , z( 0 )
  {}

  Vec3::Vec3( f32 xyz[ 3 ] )
    : x( xyz[ 0 ] )
    , y( xyz[ 1 ] )
    , z( xyz[ 2 ] )
  {}

  Vec3::Vec3( f32 x, f32 y, f32 z )
    : x( x )
    , y( y )
    , z( z )
  {}

  Vec3::Vec3( f32 xyz )
    : x( xyz )
    , y( xyz )
    , z( xyz )
  {}

  Vec3::Vec3( const Vec2& vec, f32 z )
    : x( vec.x )
    , y( vec.y )
    , z( z     )
  {}

  Vec3::Vec3( const Vec4& vec )
    : x( vec.x )
    , y( vec.y )
    , z( vec.z )
  {}

  Vec3::Vec3( const Vec3& vec )
      : x( vec.x )
      , y( vec.y )
      , z( vec.z )
    {}

  Vec3::Vec3( Vec3&& vec )
    : x( vec.x )
    , y( vec.y )
    , z( vec.z )
  {}

  /////////////////////////////////

  Vec3 cross( const Vec3& a, const Vec3& b )
  {
    return Vec3{ a.y * b.z - b.y * a.z,
                 a.z * b.x - b.z * a.x,
                 a.x * b.y - b.x * a.y };
  }
}