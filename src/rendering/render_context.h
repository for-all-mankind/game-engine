#ifndef ICE_RENDER_CONTEXT_H
#define ICE_RENDER_CONTEXT_H

#include "../maths/mat4.h"

namespace Ice
{
  // I can't think of anything else to
  // put in here at the moment, but I'm sure
  // there is something.
  // Maybe something to do with shaders?

  struct RenderContext
  {
    Mat4 projection;

    bool wire_frame;
  };
}

#endif // ICE_RENDER_CONTEXT_H