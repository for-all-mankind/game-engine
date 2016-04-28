#ifndef ICE_MATHS_VEC4_HPP
#define ICE_MATHS_VEC4_HPP

#include "Common.hpp"
#include "Types.hpp"
#include "Functions.hpp"
#include <cmath>

namespace Ice
{
  struct Vec2;
  struct Vec3;

  /////////////////////////////////

  struct Vec4
  {
    Vec4();
    Vec4( f32 xyzw[ 4 ] );
    Vec4( f32 x, f32 y, f32 z, f32 w );

    explicit Vec4( f32 xyzw );
    explicit Vec4( const Vec2& vec, f32 z, f32 w );
    explicit Vec4( const Vec2& xy, const Vec2& zw );
    explicit Vec4( const Vec3& vec, f32 w );

    Vec4( const Vec4&  vec );
    Vec4(       Vec4&& vec );

    inline Vec4& operator=( const Vec4&  vec )
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = vec.w;

      return *this;
    }

    inline Vec4& operator=( Vec4&& vec )
    {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = vec.w;

      return *this;
    }

    inline       f32& operator[]( usize index )       { return elements[ index ]; }
    inline const f32& operator[]( usize index ) const { return elements[ index ]; }

    inline Vec4 operator+( const Vec4& r ) const { return Vec4{ x + r.x, y + r.y, z + r.z, w + r.w }; }
    inline Vec4 operator-( const Vec4& r ) const { return Vec4{ x - r.x, y - r.y, z - r.z, w - r.w }; }
    inline Vec4 operator*(       f32   r ) const { return Vec4{ x * r  , y * r  , z * r  , w * r   }; }
    inline Vec4 operator/(       f32   r ) const { return Vec4{ x / r  , y / r  , z / r  , w / r   }; }

    // Hadamard Product
    // inline Vec4 operator*( const Vec4& r ) const
    // {
    //   return Vec4{ x * r.x,
    //                y * r.y,
    //                z * r.z,
    //                w * r.w };
    // }

    inline Vec4& operator+=( const Vec4& r ) { return ( *this = (*this) + r ); }
    inline Vec4& operator-=( const Vec4& r ) { return ( *this = (*this) - r ); }
    inline Vec4& operator*=(       f32   r ) { return ( *this = (*this) * r ); }
    inline Vec4& operator/=(       f32   r ) { return ( *this = (*this) / r ); }

    inline bool operator==( const Vec4& other ) const
    {
      return x == other.x
          && y == other.y
          && z == other.z
          && w == other.w;
    }

    inline bool operator!=( const Vec4& other ) const
    {
      return !operator==( other );
    }

    union
    {
      f32 elements[ 4 ];

      struct { f32 x, y, z, w; };
      struct { f32 r, g, b, a; };
      struct { f32 s, t, p, q; };
    };
  };

  /////////////////////////////////

  const Vec4 Vec4_Zero  = Vec4{ 0.0f, 0.0f, 0.0f, 0.0f };
  const Vec4 Vec4_One   = Vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
  const Vec4 Vec4_UnitX = Vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
  const Vec4 Vec4_UnitY = Vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
  const Vec4 Vec4_UnitZ = Vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
  const Vec4 Vec4_UnitW = Vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

  /////////////////////////////////

  VECTOR_FUNCTIONS( 4, Vec4 )

  /////////////////////////////////

  inline std::ostream& operator<<( std::ostream& stream, const Vec4& v )
  {
    return stream << "Vec4<(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")>";
  }

}

#endif // ICE_MATHS_VEC4_HPP