#include <Ice/Transform.hpp>
#include <Ice/Maths.hpp>

namespace Ice
{
  const glm::mat4& Transform::GetTransform()
  {
    if ( _has_changed )
    {
      _model = glm::translate( glm::mat4( 1.0f ), _translation      )
             * glm::rotate   ( glm::mat4( 1.0f ), _angle, _rotation )
             * glm::scale    ( glm::mat4( 1.0f ), _scale            );

      _has_changed = false;
    }

    return _model;
  }

  void Transform::SetTranslation( const glm::vec3& vec )
  {
    _has_changed = true;
    _translation = vec;
  }

  void Transform::SetScale( const glm::vec3& vec )
  {
    _has_changed = true;
    _scale       = vec;
  }

  void Transform::SetRotation( f32 angle, const glm::vec3& axis )
  {
    _has_changed = true;

    _angle    = angle;
    _rotation = axis;
  }

  glm::vec3 Transform::GetTranslation() const { return _translation; }
  glm::vec3 Transform::GetScale      () const { return _scale;       }

  glm::vec3 Transform::GetRotationAxis () const { return _rotation; }
  f32       Transform::GetRotationAngle() const { return _angle;    }
}