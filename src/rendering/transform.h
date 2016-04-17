#ifndef ICE_TRANSFORM_H
#define ICE_TRANSFORM_H

#include "../maths/maths.h"

namespace Ice
{
  class Transform
  {
  public:
    Transform()
      : _has_changed( true       )
      , _translation( Vec3::Zero )
      , _scale      ( Vec3::One  )
      , _rotation   ( Vec3::Zero )
      , _angle      ( 0.0f       )
    {}

    const Mat4& GetModel();
    // Mat4 GetProjected( const Mat4& projection );

    void SetTranslation( const Vec3& vec );
    void SetScale      ( const Vec3& vec );

    void SetRotation( f32 angle, const Vec3& vec );

    Vec3 GetTranslation() const;
    Vec3 GetScale      () const;

    Vec3 GetRotationAmount() const;
    f32  GetRotationAngle () const;

  private:
    bool _has_changed;
    Mat4 _model;
    Vec3 _translation;
    Vec3 _scale;
    Vec3 _rotation;
    f32  _angle;
  };
}

#endif // ICE_TRANSFORM_H