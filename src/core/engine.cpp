#include "engine.h"
// #include "../script/pnl.h"
#include "../util/file.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace Ice
{
  static void error_callback( i32 error, const char* description )
  {
    std::cout << "Error: " << error
              << ": "      << description
              << std::endl;
  }

  /////////////////////////////////

  Engine::Engine()
   : _window  ( nullptr )
   , _renderer( nullptr )
  {
    glfwInit();
    glfwSetErrorCallback( error_callback );
  }

  Engine::~Engine()
  {
    if ( _window != nullptr )
      delete _window;

    if ( _renderer != nullptr )
      delete _renderer;

    glfwTerminate();
  }

  bool Engine::InitWindow()
  {
    std::cout << "Creating window... " << std::endl;

    WindowConfig cfg;    // The configuration parameters for the window.
    // PnlVm        pnl;    // An instance of the pnl engine for loading the configuration.

    // bool write_config = false;

    // The default configuration parameters.
    cfg.title      = "Ice Engine";
    cfg.width      = 800;
    cfg.height     = 600;
    cfg.fullscreen = false;

    // The configuration file path.
    // std::string window_prefs = "./cfg/window_prefs.pnl";



    // TODO:
    // Use a try catch here once the window's constructor
    // throws errors on failure.

    _window   = new Window{ std::move( cfg ) };
    _renderer = new Renderer{};

    // TODO:
    // Make these configurable inside the game.
    _context_ui   .projection = Mat4::Orthographic( -1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 1000.0f );
    _context_scene.projection = Mat4::Perspective ( 70.0f, 45.0f, 0.01f, 1000.0f );

    // TODO:
    // Use the PnlVm to save and load window configuration
    // files.


    // TODO:
    // The rendering engine will be initialised here too,
    // since OpenGL can't do anything until the context is
    // created and that is handled by the window.

    return true;
  }

  bool Engine::InitAudio()
  {
    std::cout << "Loading audio... " << std::endl;


    return true;
  }

  bool Engine::InitMods()
  {
    std::cout << "Loading mods... " << std::endl;
    // TODO:
    // PnlVm pnl;

    // pnl.NewTable();

    return true;
  }

  void Engine::Run()
  {
    // The window hasn't been initialised yet, so
    // we can't do anything.
    if ( _window == nullptr )
    {
      std::cout << "The window is not initialised." << std::endl;
      return;
    }

    while ( _window->IsOpen() )
    {
      // Clear the screen
      _renderer->Clear();

      _window->Update();

      // Update everything.
      _ui   .Update();
      _scene.Update();

      // Render everything.
      _renderer->Render( _ui   , _context_ui    );
      _renderer->Render( _scene, _context_scene );

      // Flip the buffers.
      _window->Flip();
    }
  }
}