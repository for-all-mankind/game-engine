#include <Ice/Maths/Vec2.hpp>
#include <Ice/Maths/Vec3.hpp>
#include <Ice/Maths/Vec4.hpp>

namespace Ice
{
  Vec2::Vec2()
    : x( 0 )
    , y( 0 )
  {}

  Vec2::Vec2( f32 xy[ 2 ] )
    : x( xy[ 0 ] )
    , y( xy[ 1 ] )
  {}

  Vec2::Vec2( f32 x, f32 y )
    : x( x )
    , y( y )
  {}

  Vec2::Vec2( f32 xy )
    : x( xy )
    , y( xy )
  {}

  Vec2::Vec2( const Vec3& vec )
    : x( vec.x )
    , y( vec.y )
  {}

  Vec2::Vec2( const Vec4& vec )
    : x( vec.x )
    , y( vec.y )
  {}

  Vec2::Vec2( const Vec2& vec )
      : x( vec.x )
      , y( vec.y )
    {}

  Vec2::Vec2( Vec2&& vec )
    : x( vec.x )
    , y( vec.y )
  {}

  /////////////////////////////////

  f32 cross( const Vec2& a, const Vec2& b )
  {
    return a.x * b.y
         - b.x * a.y;
  }
}