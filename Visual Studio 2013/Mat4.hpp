#ifndef ICE_MATHS_MAT4_HPP
#define ICE_MATHS_MAT4_HPP

#include "Types.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Quaternion.hpp"

namespace Ice
{
  const usize MATRIX_WIDTH = 4;
  const usize MATRIX_SIZE  = MATRIX_WIDTH * MATRIX_WIDTH;

  /////////////////////////////////

  struct Mat4
  {
  public:
    Mat4( f32 val = 1.0f );
    Mat4( f32 e0, f32 e4, f32 e8 , f32 e12,
          f32 e1, f32 e5, f32 e9 , f32 e13,
          f32 e2, f32 e6, f32 e10, f32 e14,
          f32 e3, f32 e7, f32 e11, f32 e15 );

          f32& operator[]( usize index )       { return elements[ index ]; }
    const f32& operator[]( usize index ) const { return elements[ index ]; }

    Mat4( const Mat4&  mat );
    Mat4(       Mat4&& mat );

    inline Mat4& operator=( const Mat4& mat )
    {
      for ( usize i = 0; i < MATRIX_SIZE; ++i )
        elements[ i ] = mat[ i ];

      return *this;
    }

    inline Mat4& operator=( Mat4&& mat )
    {
      for ( usize i = 0; i < MATRIX_SIZE; ++i )
        elements[ i ] = mat[ i ];

      return *this;
    }

    bool operator==( const Mat4& other )
    {
      for ( usize i = 0; i < MATRIX_SIZE; ++i )
        if ( elements[ i ] != other[ i ] )
          return false;

      return true;
    }

    bool operator!=( const Mat4& other )
    {
      return !operator==( other );
    }

    Mat4 operator*( const Mat4& r ) const
    {
      Mat4 result;

      for ( usize x = 0; x < MATRIX_WIDTH; ++x )
        for ( usize y = 0; y < MATRIX_WIDTH; ++y )
        {
          result[ x + y * MATRIX_WIDTH ]
            = elements[ x + 0 * MATRIX_WIDTH ] * r[ 0 + y * MATRIX_WIDTH ]
            + elements[ x + 1 * MATRIX_WIDTH ] * r[ 1 + y * MATRIX_WIDTH ]
            + elements[ x + 2 * MATRIX_WIDTH ] * r[ 2 + y * MATRIX_WIDTH ]
            + elements[ x + 3 * MATRIX_WIDTH ] * r[ 3 + y * MATRIX_WIDTH ];
        }

      return result;
    }

    Vec4 operator*( const Vec4& r ) const
    {
      Vec4 result;

      for ( usize i = 0; i < MATRIX_SIZE; ++i );
        // result += columns[0] * r;

      return result;
    }

    Mat4 operator*( f32 r ) const
    {
      Mat4 result;

      for ( usize i = 0; i < MATRIX_SIZE; ++i )
        result[i] = elements[i] * r;

      return result;
    }

    Mat4 operator/( f32 r ) const
    {
      Mat4 result;

      for ( usize i = 0; i < MATRIX_SIZE; ++i )
        result[i] = elements[i] / r;

      return result;
    }

    Mat4& operator*=( const Mat4& r ) { return ( *this = (*this) * r ); }

  public:
    // column major ordering [ row + column * width ]
    //                       [ x   + y      * width ]
    f32  elements[ MATRIX_SIZE ];
  };

  /////////////////////////////////

  inline Mat4 operator*( f32 l, const Mat4& r )
  {
    Mat4 result;

    for ( usize i = 0; i < MATRIX_SIZE; ++i )
      result[i] = l * r[i];

    return result;
  }

  void transpose (       Mat4& mat );
  Mat4 transposed( const Mat4& mat );

  Mat4 translate( const Vec3& position );
  Mat4 scale    ( const Vec3& scale    );

  // Angle in radians.
  Mat4 rotate( const Quaternion& quat );

  Mat4 orthographic( f32 left, f32 right , f32 top , f32 bottom, f32 near, f32 far );
  Mat4 perspective ( f32 fov , f32 aspect, f32 near, f32 far );

  Mat4 look_at( const Vec3& origin,
                const Vec3& target,
                const Vec3& up );

  std::ostream& operator<<( std::ostream& stream, const Mat4& mat );
}

#endif // ICE_MATHS_MAT4_HPP