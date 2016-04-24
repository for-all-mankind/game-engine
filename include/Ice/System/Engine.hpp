#ifndef ICE_ENGINE_H
#define ICE_ENGINE_H

#include <Ice/Common/Types.hpp>
#include <Ice/System/Window.hpp>
#include <Ice/System/Time.hpp>
#include <Ice/Graphics/RenderContext.hpp>
#include <Ice/Graphics/Renderer.hpp>

namespace Ice
{
  class Engine
  {
  public:
    Engine();
    ~Engine();

    // One method to rule them.
    void Run();

  private:
    // The subsystem initialisation methods
    bool InitWindow();
    bool InitAudio();
    bool InitGUI();
    bool InitMods();

  private:
    Window*   _window;
    Renderer* _renderer;

    RenderContext _context_ui;
    RenderContext _context_scene;

    TickCounter _tick_counter;
    Clock       _clock;
  };
}

#endif // ICE_ENGINE_H