#ifndef ICE_TRANSFORM_H
#define ICE_TRANSFORM_H

#include <Ice/Common/Types.hpp>
#include <Ice/Maths/Maths.hpp>

namespace Ice
{
  class Transform
  {
  public:
    Transform()
      : _has_changed( true     )
      , _scale      ( Vec3_One )
    {}

    const Mat4& GetTransform();

    void SetTranslation( const Vec3& vec );
    void SetScale      ( const Vec3& vec );

    void SetRotation( const Quaternion& quat );

    Vec3 GetTranslation() const;
    Vec3 GetScale      () const;

    Quaternion GetRotation() const;

  private:
    bool _has_changed;
    Mat4 _model;

    Vec3 _translation;
    Vec3 _scale;

    Quaternion _rotation;
  };
}

#endif // ICE_TRANSFORM_H