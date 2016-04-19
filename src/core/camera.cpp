#include "camera.h"
#include "../maths/defines.h"

#include <glm/glm.hpp>

namespace Ice
{
  Camera::Camera()
    : _position( Vec3_Zero  )
    , _forward ( Vec3_UnitZ )
    , _up      ( Vec3_UnitY )

    , _yaw        ( YAW         )
    , _pitch      ( PITCH       )
    , _speed      ( SPEED       )
    , _sensitivity( SENSITIVITY )
    , _zoom       ( ZOOM_MAX    )
  {
    UpdateVectors();
  }

  Camera::Camera( const glm::vec3& position,
                  const glm::vec3& forward,
                  const glm::vec3& up )
    : _position( position )
    , _forward ( forward  )
    , _up      ( up       )

    , _yaw        ( YAW         )
    , _pitch      ( PITCH       )
    , _speed      ( SPEED       )
    , _sensitivity( SENSITIVITY )
    , _zoom       ( ZOOM_MAX    )
  {
    UpdateVectors();
  }

  void Camera::Move( const glm::vec3& direction, f32 delta )
  {
    _position += direction * ( _speed * delta );
  }

  void Camera::LookAt( const glm::vec3& target )
  {

  }

  void Camera::Rotate( f32 xoffset, f32 yoffset )
  {
    xoffset *= _sensitivity;
    yoffset *= _sensitivity;

    _yaw   += xoffset;
    _pitch += xoffset;

    if ( _pitch > 89.0f )
      _pitch = 89.0f;
    if ( _pitch < -89.0f )
      _pitch = -89.0f;

    UpdateVectors();
  }

  void Camera::Zoom( f32 offset )
  {
    if ( _zoom >= ZOOM_MIN && _zoom <= ZOOM_MAX )
      _zoom -= offset;
    if ( _zoom <= ZOOM_MIN )
      _zoom = ZOOM_MIN;
    if ( _zoom >= ZOOM_MAX )
      _zoom = ZOOM_MAX;
  }

  glm::vec3& Camera::Position() { return _position; }
  glm::vec3& Camera::Forward () { return _forward;  }
  glm::vec3& Camera::Up      () { return _up;       }
  glm::vec3& Camera::Right   () { return _right;    }

  void Camera::UpdateVectors()
  {
    f32 cos_pitch = cosf( glm::radians( _pitch ) );
    f32 sin_pitch = sinf( glm::radians( _pitch ) );
    f32 cos_yaw   = cosf( glm::radians( _yaw   ) );
    f32 sin_yaw   = sinf( glm::radians( _yaw   ) );

    glm::vec3 forward = glm::vec3( cos_yaw * cos_pitch,
                                   sin_pitch,
                                   sin_yaw * cos_pitch );

    _forward = glm::normalize( forward );
    _right   = glm::normalize( glm::cross( _forward, Vec3_UnitY ) );
    _up      = glm::normalize( glm::cross( _right  , _forward   ) );
  }
}