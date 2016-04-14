#ifndef ICE_ENGINE_H
#define ICE_ENGINE_H

#include "window.h"
#include "../scene/node.h"

#include <SDL2/SDL.h>

namespace Ice
{
  class Engine
  {
  public:
    Engine();
    ~Engine();

    // The subsystem initialisation methods
    bool InitWindow( const WindowConfig&& cfg );

    // One method to rule them.
    void Run();

  private:
    Window* _window;

    NodeRef _scene;
    NodeRef _ui;
  };
}

#endif // ICE_ENGINE_H