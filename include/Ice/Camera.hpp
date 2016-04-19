#ifndef ICE_CAMERA_H
#define ICE_CAMERA_H

#include <Ice/Common/Types.hpp>
#include <Ice/Maths.hpp>

namespace Ice
{
  const f32 YAW         = -90.0f;
  const f32 PITCH       =  0.0f;
  const f32 SPEED       =  3.0f;
  const f32 SENSITIVITY =  0.25f;
  const f32 ZOOM_MIN    =  1.0f;
  const f32 ZOOM_MAX    =  45.0f;

  class Camera
  {
  public:
    Camera();
    Camera( const glm::vec3& position,
            const glm::vec3& forward,
            const glm::vec3& up );

    void Move  ( const glm::vec3& direction, f32 delta );
    void LookAt( const glm::vec3& target );

    void Rotate( f32 xoffset, f32 yoffset );
    void Zoom  ( f32 offset );

    glm::vec3& Position();
    glm::vec3& Forward ();
    glm::vec3& Up      ();
    glm::vec3& Right   ();

  private:
    void UpdateVectors();

  private:
    glm::vec3 _position;
    glm::vec3 _forward;
    glm::vec3 _up;
    glm::vec3 _right;

    f32 _yaw;
    f32 _pitch;
    f32 _speed;
    f32 _sensitivity;
    f32 _zoom;
  };
}

#endif // ICE_CAMERA_H