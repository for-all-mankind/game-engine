#include <Ice/Transform.hpp>

namespace Ice
{
  const Mat4& Transform::GetTransform()
  {
    if ( _has_changed )
    {
      // _model = translate( _translation )
      //        * rotate   ( _rotation    )
      //        * scale    ( _scale       );

      _model = translate( _translation )
             * scale    ( _scale       );

      _has_changed = false;
    }

    return _model;
  }

  void Transform::SetTranslation( const Vec3& vec )
  {
    _has_changed = true;
    _translation = vec;
  }

  void Transform::SetScale( const Vec3& vec )
  {
    _has_changed = true;
    _scale       = vec;
  }

  void Transform::SetRotation( const Quaternion& quat )
  {
    _has_changed = true;
    _rotation    = quat;
  }

  Vec3 Transform::GetTranslation() const { return _translation; }
  Vec3 Transform::GetScale      () const { return _scale;       }

  Quaternion Transform::GetRotation() const { return _rotation; }
}