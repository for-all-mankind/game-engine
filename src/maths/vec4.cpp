#include "vec4.h"

namespace Ice
{
  Vec4::Vec4()
    : X( 0.0f )
    , Y( 0.0f )
    , Z( 0.0f )
    , W( 0.0f )
  {}

  Vec4::Vec4( f32 x, f32 y, f32 z, f32 w )
    : X( x )
    , Y( y )
    , Z( z )
    , W( w )
  {}

  const Vec4 Vec4::Zero ( 0.0f, 0.0f, 0.0f, 0.0f );
  const Vec4 Vec4::One  ( 1.0f, 1.0f, 1.0f, 1.0f );
  const Vec4 Vec4::UnitX( 1.0f, 0.0f, 0.0f, 0.0f );
  const Vec4 Vec4::UnitY( 0.0f, 1.0f, 0.0f, 0.0f );
  const Vec4 Vec4::UnitZ( 0.0f, 0.0f, 1.0f, 0.0f );
  const Vec4 Vec4::UnitW( 0.0f, 0.0f, 0.0f, 1.0f );

  Vec4 Vec4::operator+( const Vec4& r ) const { return Vec4{ X + r.X, Y + r.Y, Z + r.Z, W + r.W }; };
  Vec4 Vec4::operator-( const Vec4& r ) const { return Vec4{ X - r.X, Y - r.Y, Z - r.Z, W - r.W }; };
  Vec4 Vec4::operator*( f32 r ) const { return Vec4{ X * r, Y * r, Z * r, W * r }; };
  Vec4 Vec4::operator/( f32 r ) const { return Vec4{ X / r, Y / r, Z / r, W / r }; };

  Vec4& Vec4::operator+=( const Vec4& r ) { X += r.X; Y += r.Y; Z += r.Z; W += r.W; return *this; };
  Vec4& Vec4::operator-=( const Vec4& r ) { X -= r.X; Y -= r.Y; Z -= r.Z; W -= r.W; return *this; };
  Vec4& Vec4::operator*=( f32 r ) { X *= r; Y *= r; Z *= r; W *= r; return *this; };
  Vec4& Vec4::operator/=( f32 r ) { X /= r; Y /= r; Z /= r; W /= r; return *this; };

  bool Vec4::operator==( const Vec4& r ) const { return ( X == r.X && Y == r.Y && Z == r.Z && W == r.W ); }
  bool Vec4::operator!=( const Vec4& r ) const { return ( X != r.X || Y != r.Y || Z != r.Z || W != r.W ); }

  std::ostream& operator<<( std::ostream& stream, const Vec4& vec )
  {
    stream << "Vec4(" << vec.X << "," << vec.Y << "," << vec.Z << "," << vec.W << ")";
    return stream;
  }
}