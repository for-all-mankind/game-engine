#include <Ice/Maths/Mat4.hpp>

namespace Ice
{
  Mat4::Mat4( f32 val )
    : elements{ val , 0.0f, 0.0f, 0.0f,
                0.0f, val , 0.0f, 0.0f,
                0.0f, 0.0f, val , 0.0f,
                0.0f, 0.0f, 0.0f, val  }
  {}

  Mat4::Mat4( f32 e0, f32 e4, f32 e8 , f32 e12,
              f32 e1, f32 e5, f32 e9 , f32 e13,
              f32 e2, f32 e6, f32 e10, f32 e14,
              f32 e3, f32 e7, f32 e11, f32 e15 )
    : elements{ e0, e4, e8 , e12,
                e1, e5, e9 , e13,
                e2, e6, e10, e14,
                e3, e7, e11, e15 }
  {}

  Mat4::Mat4( const Mat4& mat )
  {
    for ( usize i = 0; i < MATRIX_SIZE; ++i )
      elements[ i ] = mat[ i ];
  }

  Mat4::Mat4( Mat4&& mat )
  {
    for ( usize i = 0; i < MATRIX_SIZE; ++i )
      elements[ i ] = mat[ i ];
  }

  /////////////////////////////////

  void transpose( Mat4& mat )
  {
    Mat4 result;

    for ( usize i = 0; i < MATRIX_WIDTH; ++i )
      for ( usize j = 0; j < MATRIX_WIDTH; ++j )
        result[ i + j * MATRIX_WIDTH ] = mat[ j + i * MATRIX_WIDTH ];

    mat = result;
  }

  Mat4 transposed( const Mat4& mat )
  {
    Mat4 result;

    for ( usize i = 0; i < MATRIX_WIDTH; ++i )
      for ( usize j = 0; j < MATRIX_WIDTH; ++j )
        result[ i + j * MATRIX_WIDTH ] = mat[ j + i * MATRIX_WIDTH ];

    return result;
  }

  Mat4 translate( const Vec3& v )
  {
    return { 1.0f, 0.0f, 0.0f, v.x ,
             0.0f, 1.0f, 0.0f, v.y ,
             0.0f, 0.0f, 1.0f, v.z ,
             0.0f, 0.0f, 0.0f, 1.0f };
  }

  Mat4 scale( const Vec3& v )
  {
    return { v.x , 0.0f, 0.0f, 0.0f,
             0.0f, v.y , 0.0f, 0.0f,
             0.0f, 0.0f, v.z , 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f };
  }

  Mat4 rotate( const Quaternion& quat )
  {
    Mat4 result;

    const f32& x = quat.v.x;
    const f32& y = quat.v.y;
    const f32& z = quat.v.z;
    const f32& w = quat.w;

    const f32 x22 = 2.0f * ( x * x );
    const f32 y22 = 2.0f * ( y * y );
    const f32 z22 = 2.0f * ( z * z );

    const f32 wx2 = 2.0f * w * x;
    const f32 wz2 = 2.0f * w * z;
    const f32 wy2 = 2.0f * w * y;
    const f32 xy2 = 2.0f * x * y;
    const f32 xz2 = 2.0f * x * z;
    const f32 yz2 = 2.0f * y * z;

    result[ 0 + 0 * MATRIX_WIDTH ] = 1.0f - y22 - z22;
    result[ 0 + 1 * MATRIX_WIDTH ] = xy2 + wz2;
    result[ 0 + 2 * MATRIX_WIDTH ] = xz2 - wy2;

    result[ 1 + 0 * MATRIX_WIDTH ] = xy2 - wz2;
    result[ 1 + 1 * MATRIX_WIDTH ] = 1.0f - x22 - z22;
    result[ 1 + 2 * MATRIX_WIDTH ] = yz2 + wx2;

    result[ 2 + 0 * MATRIX_WIDTH ] = xz2 + wy2;
    result[ 2 + 1 * MATRIX_WIDTH ] = yz2 - wx2;
    result[ 2 + 2 * MATRIX_WIDTH ] = 1.0f - x22 - y22;

    return result;
  }

  Mat4 orthographic( f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far )
  {
    Mat4 result;

    f32 rl = right - left;
    f32 tb = top   - bottom;
    f32 fn = far   - near;

    result[ 0 + 0 * MATRIX_WIDTH ] =  2.0f / rl;
    result[ 1 + 1 * MATRIX_WIDTH ] =  2.0f / tb;
    result[ 2 + 2 * MATRIX_WIDTH ] = -2.0f / fn;

    result[ 3 + 0 * MATRIX_WIDTH ] = -( right + left   ) / rl;
    result[ 3 + 1 * MATRIX_WIDTH ] = -( top   + bottom ) / tb;
    result[ 3 + 2 * MATRIX_WIDTH ] = -( far   + near   ) / fn;

    return result;
  }

  Mat4 perspective( f32 fov, f32 aspect, f32 near, f32 far )
  {
    assert( std::fabs( aspect - std::numeric_limits<f32>::epsilon() ) > 0.0f );

    const f32 ar  = aspect;
    const f32 thf = tanf( fov / 2.0f );
    const f32 zr  = near - far;

    return { 1.0f / ( thf * ar ), 0.0f      , 0.0f                , 0.0f,
             0.0f               , 1.0f / thf, 0.0f                , 0.0f,
             0.0f               , 0.0f      , ( -near - far ) / zr, 2.0f * far * near / zr,
             0.0f               , 0.0f      , 1.0f                , 0.0f };
  }

  Mat4 look_at( const Vec3& origin,
                const Vec3& target,
                const Vec3& up )
  {
    Mat4 result;

    const Vec3 f = normalised( target - origin );
    const Vec3 s = normalised( cross( f, up ) );
    const Vec3 u = cross( s, f );

    return { +s.x , +u.x , -f.x , -dot( s, origin ),
             +s.y , +u.y , -f.y , -dot( u, origin ),
             +s.z , +u.z , -f.z , +dot( f, origin ),
             +0.0f, +0.0f, +0.0f, +1.0f             };
  }

  std::ostream& operator<<( std::ostream& stream, const Mat4& mat )
  {
    stream << "Mat4<(";

    for ( usize i = 0; i < MATRIX_WIDTH; ++i )
    {
      stream << "\t";
      for ( usize j = 0; j < MATRIX_WIDTH; ++j )
      {
         stream << mat[ i + j * MATRIX_WIDTH ];

         if ( j != 3 )
            stream << ", ";
      }
      stream << "\n";
    }

    return stream << ")>\n";
  }
}