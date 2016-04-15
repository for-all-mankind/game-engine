#ifndef ICE_ENGINE_H
#define ICE_ENGINE_H

#include "window.h"
#include "../scene/node.h"
#include "../rendering/render_context.h"
#include "../rendering/renderer.h"

namespace Ice
{
  class Engine
  {
  public:
    Engine();
    ~Engine();

    // The subsystem initialisation methods
    bool InitWindow();
    bool InitAudio();
    bool InitMods();

    // One method to rule them.
    void Run();

  private:
    Window*   _window;
    Renderer* _renderer;

    RenderContext _context_ui;
    RenderContext _context_scene;

    NodeRef _ui;
    NodeRef _scene;
  };
}

#endif // ICE_ENGINE_H