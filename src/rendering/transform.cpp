#include "transform.h"

namespace Ice
{
  // Mat4 Transform::GetModel()
  // {
  //   Mat4 translation = Mat4::Translation( _translation      );
  //   Mat4 scale       = Mat4::Scale      ( _scale            );
  //   Mat4 rotation    = Mat4::Rotation   ( _angle, _rotation );

  //   Mat4 model = translation * rotation * scale;
  // }

  // Mat4 Transform::GetProjected( const Mat4& projection )
  // {
  //   return GetModel() * projection;
  // }

  void Transform::SetTranslation( const Vec3& vec ) { _translation = vec; }
  void Transform::SetScale      ( const Vec3& vec ) { _scale       = vec; }

  void Transform::SetRotation( f32 angle, const Vec3& vec )
  {
    _angle    = angle;
    _rotation = vec;
  }

  Vec3 Transform::GetTranslation() const { return _translation; }
  Vec3 Transform::GetScale      () const { return _scale;       }

  Vec3 Transform::GetRotationAmount() const { return _rotation; }
  f32  Transform::GetRotationAngle () const { return _angle;    }
}