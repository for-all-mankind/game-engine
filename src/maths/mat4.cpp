#include "mat4.h"
#include "maths_util.h"

namespace Ice
{
  Mat4::Mat4()
  {
    for ( u32 i = 0; i < MATRIX_SIZE; ++i )
      Elements[i] = 0.0f;
  }

  Mat4::Mat4( f32 diagonal )
  {
    for ( u32 i = 0; i < MATRIX_SIZE; ++i )
    {
      if ( i % 5 == 0 )
        Elements[i] = diagonal;
      else
        Elements[i] = 0.0f;
    }
  }

  Vec3 Mat4::operator*( const Vec3& r ) const
  {
    return Vec3(
      Columns[ 0 ].X * r.X + Columns[ 1 ].X * r.Y + Columns[ 2 ].X * r.Z + Columns[ 3 ].X,
      Columns[ 0 ].Y * r.X + Columns[ 1 ].Y * r.Y + Columns[ 2 ].Y * r.Z + Columns[ 3 ].Y,
      Columns[ 0 ].Z * r.X + Columns[ 1 ].Z * r.Y + Columns[ 2 ].Z * r.Z + Columns[ 3 ].Z
    );
  }

  Vec4 Mat4::operator*( const Vec4& r ) const
  {
    return Vec4(
      Columns[ 0 ].X * r.X + Columns[ 1 ].X * r.Y + Columns[ 2 ].X * r.Z + Columns[ 3 ].X * r.W,
      Columns[ 0 ].Y * r.X + Columns[ 1 ].Y * r.Y + Columns[ 2 ].Y * r.Z + Columns[ 3 ].Y * r.W,
      Columns[ 0 ].Z * r.X + Columns[ 1 ].Z * r.Y + Columns[ 2 ].Z * r.Z + Columns[ 3 ].Z * r.W,
      Columns[ 0 ].W * r.X + Columns[ 1 ].W * r.Y + Columns[ 2 ].W * r.Z + Columns[ 3 ].W * r.W
    );
  }

  Mat4 Mat4::operator*( const Mat4& r ) const
  {
    Mat4 result;

    for ( u32 y = 0; y < MATRIX_WIDTH; ++y )
    {
      for ( u32 x = 0; x < MATRIX_WIDTH; ++x )
      {
        result.Elements[ x + y * MATRIX_WIDTH ] =
          Elements[ x + 0 * MATRIX_WIDTH ] * r.Elements[ 0 + y * MATRIX_WIDTH ] +
          Elements[ x + 1 * MATRIX_WIDTH ] * r.Elements[ 1 + y * MATRIX_WIDTH ] +
          Elements[ x + 2 * MATRIX_WIDTH ] * r.Elements[ 2 + y * MATRIX_WIDTH ] +
          Elements[ x + 3 * MATRIX_WIDTH ] * r.Elements[ 3 + y * MATRIX_WIDTH ];
      }
    }

    return result;
  }

  Mat4& Mat4::operator*=( const Mat4& r )
  {
    (*this) = (*this) * r;

    return *this;
  }

  // Static Methods
  Mat4 Mat4::Identity()
  {
    return Mat4( 1.0f );
  }

  Mat4 Mat4::Orthographic( f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far )
  {
    Mat4 result( 1.0f );

    result.Elements[ 0 + 0 * MATRIX_WIDTH ] = 2.0f / ( right - left   );
    result.Elements[ 1 + 1 * MATRIX_WIDTH ] = 2.0f / ( top   - bottom );
    result.Elements[ 2 + 2 * MATRIX_WIDTH ] = 2.0f / ( near  - far    );

    result.Elements[ 0 + 3 * MATRIX_WIDTH ] = ( left   + right ) / ( left   - right );
    result.Elements[ 1 + 3 * MATRIX_WIDTH ] = ( bottom + top   ) / ( bottom - top   );
    result.Elements[ 2 + 3 * MATRIX_WIDTH ] = ( far    + near  ) / ( far    - near  );

    return result;
  }

  Mat4 Mat4::Perspective( f32 fov, f32 aspect, f32 near, f32 far )
  {
    Mat4 result;

    f32 q = 1.0f / tan( to_radians( 0.5f * fov ) );
    f32 a = q    / aspect;

    f32 b =        ( far + near ) / ( far - near );
    f32 c = ( 2.0f * far * near ) / ( far - near );

    result.Elements[ 0 + 0 * MATRIX_WIDTH ] = a;
    result.Elements[ 1 + 1 * MATRIX_WIDTH ] = q;
    result.Elements[ 2 + 2 * MATRIX_WIDTH ] = b;

    result.Elements[ 3 + 2 * MATRIX_WIDTH ] = -1.0f;
    result.Elements[ 2 + 3 * MATRIX_WIDTH ] = c;

    return result;
  }

  Mat4 Mat4::Translation( f32 x, f32 y, f32 z )
  {
    Mat4 result( 1.0f );

    result.Elements[ 0 + 3 * MATRIX_WIDTH ] = x;
    result.Elements[ 1 + 3 * MATRIX_WIDTH ] = y;
    result.Elements[ 2 + 3 * MATRIX_WIDTH ] = z;

    return result;
  }

  Mat4 Mat4::Scale( f32 x, f32 y, f32 z )
  {
    Mat4 result( 1.0f );

    result.Elements[ 0 + 0 * MATRIX_WIDTH ] = x;
    result.Elements[ 1 + 1 * MATRIX_WIDTH ] = y;
    result.Elements[ 2 + 2 * MATRIX_WIDTH ] = z;

    return result;
  }

  Mat4 Mat4::Rotation( f32 a, f32 x, f32 y, f32 z )
  {
    Mat4 result( 1.0f );

    f32 r = to_radians( a );
    f32 c = cos( r );
    f32 s = sin( r );
    f32 o = 1.0f - c;

    result.Elements[ 0 + 0 * MATRIX_WIDTH ] = x * o + c;
    result.Elements[ 1 + 0 * MATRIX_WIDTH ] = y * x * o + z * s;
    result.Elements[ 2 + 0 * MATRIX_WIDTH ] = x * z * o - y * s;

    result.Elements[ 0 + 1 * MATRIX_WIDTH ] = x * y * o - z * s;
    result.Elements[ 1 + 1 * MATRIX_WIDTH ] = y * o + c;
    result.Elements[ 2 + 1 * MATRIX_WIDTH ] = y * z * o + x * s;

    result.Elements[ 0 + 2 * MATRIX_WIDTH ] = x * z * o + y * s;
    result.Elements[ 1 + 2 * MATRIX_WIDTH ] = y * z * o - x * s;
    result.Elements[ 2 + 2 * MATRIX_WIDTH ] = z * o + c;

    return result;
  }

  Mat4 Mat4::Translation( const Vec3& translation )
  {
    return Mat4::Translation( translation.X, translation.Y, translation.Z );
  }

  Mat4 Mat4::Scale( const Vec3& scale )
  {
    return Mat4::Scale( scale.X, scale.Y, scale.Z );
  }

  Mat4 Mat4::Rotation( f32 angle, const Vec3& axis )
  {
    return Mat4::Rotation( angle, axis.X, axis.Y, axis.Z );
  }

  // Printable
  std::ostream& operator<<( std::ostream& stream, const Mat4& mat )
  {
    stream << "Mat4:\n"
           << mat.Elements[0] << "|" << mat.Elements[4] << "|" << mat.Elements[8 ] << "|" << mat.Elements[12] << "\n"
           << mat.Elements[1] << "|" << mat.Elements[5] << "|" << mat.Elements[9 ] << "|" << mat.Elements[13] << "\n"
           << mat.Elements[2] << "|" << mat.Elements[6] << "|" << mat.Elements[10] << "|" << mat.Elements[14] << "\n"
           << mat.Elements[3] << "|" << mat.Elements[7] << "|" << mat.Elements[11] << "|" << mat.Elements[15] << "\n";

    return stream;
  }
}