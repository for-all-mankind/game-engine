#include "transform.h"

namespace Ice
{
  const Mat4& Transform::GetTransform()
  {
    if ( _has_changed )
    {
      _model = Mat4::Translation( _translation )
             * Mat4::Rotation   ( _rotation    )
             * Mat4::Scale      ( _scale       );

      _has_changed = false;
    }

    return _model;
  }

  // Mat4 Transform::GetProjected( const Mat4& projection )
  // {
  //   return GetTransform() * projection;
  // }

  void Transform::SetTranslation( const Vec3& vec )
  {
    _has_changed = true;
    _translation = vec;
  }

  void Transform::SetRotation( const Vec3& vec )
  {
    _has_changed = true;
    _rotation    = vec;
  }

  void Transform::SetScale( const Vec3& vec )
  {
    _has_changed = true;
    _scale       = vec;
  }

  Vec3 Transform::GetTranslation() const { return _translation; }
  Vec3 Transform::GetRotation   () const { return _rotation;    }
  Vec3 Transform::GetScale      () const { return _scale;       }
}