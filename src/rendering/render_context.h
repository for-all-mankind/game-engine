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

    bool wire_frame; // Tells the renderer to use wire frame or not.
    bool has_depth;  // Determines if the context is 2D or 3D.
  };
}

#endif // ICE_RENDER_CONTEXT_H