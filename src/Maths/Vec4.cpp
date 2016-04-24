#include <Ice/Maths/Vec2.hpp>
#include <Ice/Maths/Vec3.hpp>
#include <Ice/Maths/Vec4.hpp>

namespace Ice
{
  Vec4::Vec4()
    : x( 0 )
    , y( 0 )
    , z( 0 )
    , w( 0 )
  {}

  Vec4::Vec4( f32 xyzw[ 4 ] )
    : x( xyzw[ 0 ] )
    , y( xyzw[ 1 ] )
    , z( xyzw[ 2 ] )
    , w( xyzw[ 3 ] )
  {}

  Vec4::Vec4( f32 x, f32 y, f32 z, f32 w )
    : x( x )
    , y( y )
    , z( z )
    , w( w )
  {}

  Vec4::Vec4( f32 xyzw )
    : x( xyzw )
    , y( xyzw )
    , z( xyzw )
    , w( xyzw )
  {}

  Vec4::Vec4( const Vec2& vec, f32 z, f32 w )
    : x( vec.x )
    , y( vec.y )
    , z( z     )
    , w( w     )
  {}

  Vec4::Vec4( const Vec2& xy, const Vec2& zw )
    : x( xy.x )
    , y( xy.y )
    , z( zw.x )
    , w( zw.y )
  {}

  Vec4::Vec4( const Vec3& vec, f32 w )
    : x( vec.x )
    , y( vec.y )
    , z( vec.z )
    , w( w     )
  {}

  Vec4::Vec4( const Vec4& vec )
      : x( vec.x )
      , y( vec.y )
      , z( vec.z )
      , w( vec.w )
    {}

  Vec4::Vec4( Vec4&& vec )
    : x( vec.x )
    , y( vec.y )
    , z( vec.z )
    , w( vec.w )
  {}

  /////////////////////////////////
}