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
      , _rotation   ( Vec3::Zero )
      , _scale      ( Vec3::One  )
    {}

    const Mat4& GetTransform();

    void SetTranslation( const Vec3& vec );
    void SetRotation   ( const Vec3& vec );
    void SetScale      ( const Vec3& vec );

    Vec3 GetTranslation() const;
    Vec3 GetRotation   () const;
    Vec3 GetScale      () const;

  private:
    bool _has_changed;
    Mat4 _model;

    Vec3 _translation;
    Vec3 _rotation;
    Vec3 _scale;
  };
}

#endif // ICE_TRANSFORM_H