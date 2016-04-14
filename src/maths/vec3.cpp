#include "vec3.h"

namespace Ice
{
  Vec3::Vec3()
    : X( 0.0f )
    , Y( 0.0f )
    , Z( 0.0f )
  {}

  Vec3::Vec3( f32 x, f32 y, f32 z )
    : X( x )
    , Y( y )
    , Z( z )
  {}

  const Vec3 Vec3::Zero ( 0.0f, 0.0f, 0.0f );
  const Vec3 Vec3::One  ( 1.0f, 1.0f, 1.0f );
  const Vec3 Vec3::UnitX( 1.0f, 0.0f, 0.0f );
  const Vec3 Vec3::UnitY( 0.0f, 1.0f, 0.0f );
  const Vec3 Vec3::UnitZ( 0.0f, 0.0f, 1.0f );

  Vec3 Vec3::operator+( const Vec3& r ) const { return Vec3{ X + r.X, Y + r.Y, Z + r.Z }; };
  Vec3 Vec3::operator-( const Vec3& r ) const { return Vec3{ X - r.X, Y - r.Y, Z - r.Z }; };
  Vec3 Vec3::operator*( f32 r ) const { return Vec3{ X * r, Y * r, Z * r }; };
  Vec3 Vec3::operator/( f32 r ) const { return Vec3{ X / r, Y / r, Z / r }; };

  Vec3& Vec3::operator+=( const Vec3& r ) { X += r.X; Y += r.Y; Z += r.Z; return *this; };
  Vec3& Vec3::operator-=( const Vec3& r ) { X -= r.X; Y -= r.Y; Z -= r.Z; return *this; };
  Vec3& Vec3::operator*=( f32 r ) { X *= r; Y *= r; Z *= r; return *this; };
  Vec3& Vec3::operator/=( f32 r ) { X /= r; Y /= r; Z /= r; return *this; };

  bool Vec3::operator==( const Vec3& r ) const { return ( X == r.X && Y == r.Y && Z == r.Z ); }
  bool Vec3::operator!=( const Vec3& r ) const { return ( X != r.X || Y != r.Y || Z != r.Z ); }

  std::ostream& operator<<( std::ostream& stream, const Vec3& vec )
  {
    stream << "Vec3(" << vec.X << "," << vec.Y << "," << vec.Z << ")";
    return stream;
  }
}