#ifndef ICE_MAT4_H
#define ICE_MAT4_H

#include "../util/types.h"
#include "vec3.h"
#include "vec4.h"
#include <iostream>

namespace Ice
{
  #define MATRIX_WIDTH 4
  #define MATRIX_SIZE MATRIX_WIDTH * MATRIX_WIDTH

  class Mat4
  {
  public:
    Mat4();
    Mat4( f32 diagonal );

    Vec3  operator* ( const Vec3& r ) const;
    Vec4  operator* ( const Vec4& r ) const;
    Mat4  operator* ( const Mat4& r ) const;
    Mat4& operator*=( const Mat4& r );

    static Mat4 Identity();

    static Mat4 Orthographic( f32 left, f32 right , f32 top , f32 bottom, f32 near, f32 far );
    static Mat4 Perspective ( f32 fov , f32 aspect, f32 near, f32 far );

    static Mat4 Translation( f32 x, f32 y, f32 z );
    static Mat4 Scale      ( f32 x, f32 y, f32 z );
    static Mat4 Rotation   ( f32 a, f32 x, f32 y, f32 z );

    static Mat4 Translation( const Vec3& translation );
    static Mat4 Scale      ( const Vec3& scale );
    static Mat4 Rotation   ( f32 angle, const Vec3& axis );

    friend std::ostream& operator<<( std::ostream& stream, const Mat4& mat );

  public:
    union
    {
      f32  Elements[ MATRIX_SIZE  ];
      Vec4 Columns [ MATRIX_WIDTH ];
    };
  };
}

#endif // ICE_MATHS_MAT4_H