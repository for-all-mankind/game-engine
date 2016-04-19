#ifndef ICE_TRANSFORM_H
#define ICE_TRANSFORM_H

#include "../maths/defines.h"
#include "../util/types.h"

#include <glm/glm.hpp>

namespace Ice
{
  class Transform
  {
  public:
    Transform()
      : _has_changed( true      )
      , _translation( Vec3_Zero )
      , _scale      ( Vec3_One  )
      , _rotation   ( Vec3_Zero )
      , _angle      ( 0.0f      )
    {}

    const glm::mat4& GetTransform();

    void SetTranslation( const glm::vec3& vec );
    void SetScale      ( const glm::vec3& vec );

    void SetRotation( f32 angle, const glm::vec3& axis );

    glm::vec3 GetTranslation() const;
    glm::vec3 GetScale      () const;

    glm::vec3 GetRotationAxis () const;
    f32  GetRotationAngle() const;

  private:
    bool _has_changed;
    glm::mat4 _model;

    glm::vec3 _translation;
    glm::vec3 _scale;

    glm::vec3 _rotation;
    f32  _angle;
  };
}

#endif // ICE_TRANSFORM_H