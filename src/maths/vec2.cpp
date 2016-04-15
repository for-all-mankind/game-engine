#include "vec2.h"

namespace Ice
{
  Vec2::Vec2()
    : X( 0.0f )
    , Y( 0.0f )
  {}

  Vec2::Vec2( f32 x, f32 y )
    : X( x )
    , Y( y )
  {}

  const Vec2 Vec2::Zero ( 0.0f, 0.0f );
  const Vec2 Vec2::One  ( 1.0f, 1.0f );
  const Vec2 Vec2::UnitX( 1.0f, 0.0f );
  const Vec2 Vec2::UnitY( 0.0f, 1.0f );

  Vec2 Vec2::operator+( const Vec2& r ) const { return Vec2{ X + r.X, Y + r.Y }; };
  Vec2 Vec2::operator-( const Vec2& r ) const { return Vec2{ X - r.X, Y - r.Y }; };
  Vec2 Vec2::operator*( f32 r ) const { return Vec2{ X * r, Y * r }; };
  Vec2 Vec2::operator/( f32 r ) const { return Vec2{ X / r, Y / r }; };

  Vec2& Vec2::operator+=( const Vec2& r ) { X += r.X; Y += r.Y; return *this; };
  Vec2& Vec2::operator-=( const Vec2& r ) { X -= r.X; Y -= r.Y; return *this; };
  Vec2& Vec2::operator*=( f32 r ) { X *= r; Y *= r; return *this; };
  Vec2& Vec2::operator/=( f32 r ) { X /= r; Y /= r; return *this; };

  bool Vec2::operator==( const Vec2& r ) const { return ( X == r.X && Y == r.Y ); }
  bool Vec2::operator!=( const Vec2& r ) const { return ( X != r.X || Y != r.Y ); }

  std::ostream& operator<<( std::ostream& stream, const Vec2& vec )
  {
    stream << "Vec2(" << vec.X << "," << vec.Y << ")";
    return stream;
  }
}