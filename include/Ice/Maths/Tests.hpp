#include <Ice/Common/Common.hpp>
#include <Ice/Maths/Maths.hpp>

namespace Ice { namespace Test {

  void test_matrix_maths()
  {
    Mat4 a( 1.5f );
    Mat4 b( 2.5f );

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Basic Matrix Operations"             << std::endl;

    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;

    // std::cout << "A + B:\n" << a + b << std::endl;
    // std::cout << "A - B:\n" << a - b << std::endl;
    std::cout << "A * B:\n" << a * b << std::endl;

    std::cout << "Translate: "   << translate( Vec3_UnitX );
    // std::cout << "Rotate: "      << rotate( Constants::Pi / 4.0f, Vec3_UnitY );
    std::cout << "Scale: "       << scale( Vec3_One );
    std::cout << "Perspective: " << perspective( Constants::Pi / 4.0f, 800.0f / 600.0f, 0.1f, 100.0f );
    std::cout << "Orthgraphic: " << orthographic( -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f );
    std::cout << "Look At: "     << look_at( Vec3_Zero, Vec3_One, Vec3_UnitY );

    std::cout << "-----------------------------------" << std::endl;
  }

  void test_vector2_maths()
  {
    const     Vec2 a{ 1.5f, 1.5f };
    const     Vec2 b{ 2.5f, 2.5f };
    constexpr f32  c = 2.0f;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Vector2 Operations"                  << std::endl;

    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "C: " << c << std::endl;

    std::cout << "A + B:\n" << a + b << std::endl;
    std::cout << "A - B:\n" << a - b << std::endl;
    // std::cout << "A * B:\n" << a * b << std::endl; // Maybe implement this...

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Vector2 Scalar Operations"                  << std::endl;

    std::cout << "A * C:\n" << a * c << std::endl;
    std::cout << "C * A:\n" << c * a << std::endl;
    std::cout << "A / C:\n" << a / c << std::endl;

    // std::cout << "B *= C:\n" << b *= c << std::endl;
    // std::cout << "B /= C:\n" << b /= c << std::endl;

    std::cout << "-----------------------------------" << std::endl;
  }

  void test_vector3_maths()
  {
    const     Vec3 a{ 1.5f, 1.5f, 1.5f };
    const     Vec3 b{ 2.5f, 2.5f, 2.5f };
    constexpr f32 c = 2.0f;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Vector3 Operations"                  << std::endl;

    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "C: " << c << std::endl;

    std::cout << "A + B:\n" << a + b << std::endl;
    std::cout << "A - B:\n" << a - b << std::endl;
    // std::cout << "A * B:\n" << a * b << std::endl; // Maybe implement this...

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Vector3 Scalar Operations"                  << std::endl;

    std::cout << "A * C:\n" << a * c << std::endl;
    std::cout << "C * A:\n" << c * a << std::endl;
    std::cout << "A / C:\n" << a / c << std::endl;

    // std::cout << "B *= C:\n" << b *= c << std::endl;
    // std::cout << "B /= C:\n" << b /= c << std::endl;

    std::cout << "-----------------------------------" << std::endl;
  }

  void test_vector4_maths()
  {
    const     Vec4 a{ 1.5f, 1.5f, 1.5f, 1.5f };
    const     Vec4 b{ 2.5f, 2.5f, 2.5f, 2.5f };
    constexpr f32 c = 2.0f;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Vector4 Operations"                  << std::endl;

    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "C: " << c << std::endl;

    std::cout << "A + B:\n" << a + b << std::endl;
    std::cout << "A - B:\n" << a - b << std::endl;
    // std::cout << "A * B:\n" << a * b << std::endl; // Maybe implement this...

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Vector4 Scalar Operations"                  << std::endl;

    std::cout << "A * C:\n" << a * c << std::endl;
    std::cout << "C * A:\n" << c * a << std::endl;
    std::cout << "A / C:\n" << a / c << std::endl;

    // std::cout << "B *= C:\n" << b *= c << std::endl;
    // std::cout << "B /= C:\n" << b /= c << std::endl;

    std::cout << "-----------------------------------" << std::endl;
  }

} }