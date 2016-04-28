#ifndef ICE_MATHS_VEC3_HPP
#define ICE_MATHS_VEC3_HPP

#include "Common.hpp"
#include "Types.hpp"
#include "Functions.hpp"
#include <cmath>

namespace Ice
{

  struct Vec2;
  struct Vec4;

  /////////////////////////////////

  struct Vec3
  {
    Vec3();
    Vec3( f32 xyz[ 3 ] );
    Vec3( f32 x, f32 y, f32 z );

    explicit Vec3( f32 xyz );
    explicit Vec3( const Vec2& vec, f32 z );
    explicit Vec3( const Vec4& vec );

    Vec3( const Vec3&  vec );
    Vec3(       Vec3&& vec );

    inline Vec3& operator=( const Vec3&  vec )
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;

      return *this;
    }

    inline Vec3& operator=( Vec3&& vec )
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;

      return *this;
    }

    inline       f32& operator[]( usize index )       { return elements[ index ]; }
    inline const f32& operator[]( usize index ) const { return elements[ index ]; }

    inline Vec3 operator+( const Vec3& r ) const { return Vec3{ x + r.x, y + r.y, z + r.z }; }
    inline Vec3 operator-( const Vec3& r ) const { return Vec3{ x - r.x, y - r.y, z - r.z }; }
    inline Vec3 operator*(       f32   r ) const { return Vec3{ x * r  , y * r  , z * r   }; }
    inline Vec3 operator/(       f32   r ) const { return Vec3{ x / r  , y / r  , z / r   }; }

    inline Vec3& operator+=( const Vec3& r ) { return ( *this = (*this) + r ); }
    inline Vec3& operator-=( const Vec3& r ) { return ( *this = (*this) - r ); }
    inline Vec3& operator*=(       f32   r ) { return ( *this = (*this) * r ); }
    inline Vec3& operator/=(       f32   r ) { return ( *this = (*this) / r ); }

    inline Vec3 operator-() const { return Vec3{ -x, -y, -z }; }

    inline bool operator==( const Vec3& other ) const
    {
      return x == other.x
          && y == other.y
          && z == other.z;
    }

    inline bool operator!=( const Vec3& other ) const
    {
      return !operator==( other );
    }

    union
    {
      f32 elements[ 3 ];

      struct { f32 x, y, z; };
      struct { f32 r, g, b; };
      struct { f32 s, t, p; };
    };
  };

  /////////////////////////////////

  const Vec3 Vec3_Zero  = Vec3{ 0.0f, 0.0f, 0.0f };
  const Vec3 Vec3_One   = Vec3{ 1.0f, 1.0f, 1.0f };
  const Vec3 Vec3_UnitX = Vec3{ 1.0f, 0.0f, 0.0f };
  const Vec3 Vec3_UnitY = Vec3{ 0.0f, 1.0f, 0.0f };
  const Vec3 Vec3_UnitZ = Vec3{ 0.0f, 0.0f, 1.0f };

  /////////////////////////////////

  VECTOR_FUNCTIONS( 3, Vec3 )

  Vec3 cross( const Vec3& a, const Vec3& b );

  /////////////////////////////////

  inline std::ostream& operator<<( std::ostream& stream, const Vec3& v )
  {
    return stream << "Vec3<(" << v.x << ", " << v.y << ", " << v.z << ")>";
  }

}

#endif // ICE_MATHS_VEC3_HPP