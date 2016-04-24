#ifndef ICE_MATHS_VEC2_HPP
#define ICE_MATHS_VEC2_HPP

#include <Ice/Common/Common.hpp>
#include <Ice/Common/Types.hpp>
#include <Ice/Maths/Functions.hpp>
#include <cmath>

namespace Ice
{

  struct Vec3;
  struct Vec4;

  /////////////////////////////////

  struct Vec2
  {
    Vec2();
    Vec2( f32 xy[ 2 ] );
    Vec2( f32 x, f32 y );

    explicit Vec2( f32 xy );
    explicit Vec2( const Vec3& vec );
    explicit Vec2( const Vec4& vec );

    Vec2( const Vec2&  vec );
    Vec2(       Vec2&& vec );

    inline Vec2& operator=( const Vec2&  vec )
    {
      x = vec.x;
      y = vec.y;

      return *this;
    }

    inline Vec2& operator=( Vec2&& vec )
    {
      x = vec.x;
      y = vec.y;

      return *this;
    }

    inline       f32& operator[]( usize index )       { return elements[ index ]; }
    inline const f32& operator[]( usize index ) const { return elements[ index ]; }

    inline Vec2 operator+( const Vec2& r ) const { return Vec2{ x + r.x, y + r.y }; }
    inline Vec2 operator-( const Vec2& r ) const { return Vec2{ x - r.x, y - r.y }; }
    inline Vec2 operator*(       f32   r ) const { return Vec2{ x * r  , y * r   }; }
    inline Vec2 operator/(       f32   r ) const { return Vec2{ x / r  , y / r   }; }

    inline Vec2& operator+=( const Vec2& r ) { return ( *this = (*this) + r ); }
    inline Vec2& operator-=( const Vec2& r ) { return ( *this = (*this) - r ); }
    inline Vec2& operator*=(       f32   r ) { return ( *this = (*this) * r ); }
    inline Vec2& operator/=(       f32   r ) { return ( *this = (*this) / r ); }

    inline bool operator==( const Vec2& other ) const
    {
      return x == other.x
          && y == other.y;
    }

    inline bool operator!=( const Vec2& other ) const
    {
      return !operator==( other );
    }

    union
    {
      f32 elements[ 2 ];

      struct { f32 x, y; };
      struct { f32 r, g; };
      struct { f32 s, t; };
    };
  };

  /////////////////////////////////

  const Vec2 Vec2_Zero  = Vec2{ 0.0f, 0.0f };
  const Vec2 Vec2_One   = Vec2{ 1.0f, 1.0f };
  const Vec2 Vec2_UnitX = Vec2{ 1.0f, 0.0f };
  const Vec2 Vec2_UnitY = Vec2{ 0.0f, 1.0f };

  /////////////////////////////////

  VECTOR_FUNCTIONS( 2, Vec2 )

  f32 cross( const Vec2& a, const Vec2& b );

  /////////////////////////////////

  inline std::ostream& operator<<( std::ostream& stream, const Vec2& v )
  {
    return stream << "Vec2<(" << v.x << ", " << v.y << ")>";
  }

}



#endif // ICE_MATHS_VEC2_HPP