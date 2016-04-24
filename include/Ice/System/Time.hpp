#ifndef ICE_TIME_HPP
#define ICE_TIME_HPP

#include <Ice/Common/Types.hpp>
#include <Ice/Common/OpenGL.hpp>

namespace Ice
{
  class Clock
  {
  public:
    f64 ElapsedTime() const;
    f64 DeltaTime();

    void Reset();

  private:
    f64 _time_started = glfwGetTime();
  };

  /////////////////////////////////

  class TickCounter
  {
  public:
    bool Update();

    size_t TickRate() const { return _tick_rate; }

  private:
    size_t _ticks;
    size_t _tick_rate;

    Clock _clock;
  };

}

#endif // ICE_TIME_HPP