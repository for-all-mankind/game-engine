#include "Time.hpp"

namespace Ice
{
  bool TickCounter::Update()
  {
    bool reset = ( _clock.ElapsedTime() >= 1.0 );

    if ( reset )
    {
      _tick_rate = _ticks;
      _ticks     = 0;

      _clock.Reset();
    }

    ++_ticks;

    return reset;
  }
}