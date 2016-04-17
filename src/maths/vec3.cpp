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

  f32 Vec3::Length() const
  {
    return sqrt( X * X
               + Y * Y
               + Z * Z );
  }

  f32 Vec3::LengthSq() const
  {
    return X * X
         + Y * Y
         + Z * Z;
  }

  f32 Vec3::Distance( const Vec3& other ) const
  {
    f32 dx = abs( X - other.X );
    f32 dy = abs( Y - other.Y );
    f32 dz = abs( Z - other.Z );

    return sqrt( dx * dx
               + dy * dy
               + dz * dz );
  }

  f32 Vec3::DistanceSq( const Vec3& other ) const
  {
    f32 dx = abs( X - other.X );
    f32 dy = abs( Y - other.Y );
    f32 dz = abs( Z - other.Z );

    return dx * dx
         + dy * dy
         + dz * dz;
  }

  f32 Vec3::Dot( const Vec3& other ) const
  {
    return X * other.X
         + Y * other.Y
         + Z * other.Z;
  }

  Vec3 Vec3::Cross( const Vec3& other ) const
  {
    return Vec3{ Y * other.Z - Z * other.Y,
                 Z * other.X - X * other.Z,
                 X * other.Y - Y * other.X };
  }

  Vec3& Vec3::Normalise()
  {
    f32 length = Length();

    X /= length;
    Y /= length;
    Z /= length;

    return *this;
  }

  Vec3 Vec3::Normalised() const
  {
    f32 length = Length();

    return Vec3{ X / length,
                 Y / length,
                 Z / length };
  }

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