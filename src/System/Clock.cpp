#include <Ice/System/Time.hpp>

namespace Ice
{
  f64 Clock::ElapsedTime() const
  {
    return glfwGetTime() - _time_started;
  }

  f64 Clock::DeltaTime()
  {
    double time_current = glfwGetTime();
    double time_delta   = time_current - _time_started;
          _time_started = time_current;

    return time_delta;
  }

  void Clock::Reset()
  {
    _time_started = glfwGetTime();
  }
}