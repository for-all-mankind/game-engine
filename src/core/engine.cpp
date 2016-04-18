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
    // Initialise the window systems
    glfwInit();
    glfwSetErrorCallback( error_callback );

    // TODO:
    // Check the status of the subsystems.
    // At the moment success is assumed.

    // Create a window and initialise the renderer.
    InitWindow();

    // Initialise the sound systems.
    // YSE::System().init();

    // Load the GUI sound files.
    InitAudio();

    // Initialise the GUI system.
    InitGUI();

    // Load the mod content.
    InitMods();
  }

  Engine::~Engine()
  {
    // Destroy the window if one exists.
    if ( _window != nullptr )
      delete _window;

    // Destroy the renderer if one exists.
    if ( _renderer != nullptr )
      delete _renderer;

    // Close down the sound system.
    // YSE::System().close();

    glfwTerminate();
  }

  bool Engine::InitWindow()
  {
    std::cout << "Creating window... " << std::endl;

    // TODO:
    // Use the IceVm to save and load window configuration
    // files.

    WindowConfig cfg;    // The configuration parameters for the window.
    // IceVm        ice;    // An instance of the ice engine for loading the configuration.

    // bool write_config = false;

    // The default configuration parameters.
    cfg.title      = "Ice Engine";
    cfg.width      = 800;
    cfg.height     = 600;
    cfg.fullscreen = false;

    // The configuration file path.
    // std::string window_prefs = "./cfg/window_prefs.ice";



    // TODO:
    // Use a try catch here once the window's constructor
    // throws errors on failure.

    _window   = new Window{ std::move( cfg ) };
    _renderer = new Renderer{};

    // TODO:
    // Make these configurable inside the game.
    _context_scene.projection = Mat4::Perspective( 45.0f, cfg.width / cfg.height, 0.1f, 100.0f );
    _context_scene.wire_frame = false;
    _context_scene.has_depth  = true;

    _context_ui.projection = Mat4::Orthographic( -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f );
    _context_ui.wire_frame = false;
    _context_ui.has_depth  = false;

    return true;
  }

  bool Engine::InitAudio()
  {
    std::cout << "Loading audio files... " << std::endl;
    return true;
  }

  bool Engine::InitGUI()
  {
    std::cout << "Initialising GUI systems... " << std::endl;
    return true;
  }

  bool Engine::InitMods()
  {
    std::cout << "Loading mod content... " << std::endl;
    // TODO:
    // IceVm ice;

    // ice.NewTable();

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
      _scene.Update();
      _ui   .Update();

      // Render everything.
      _renderer->Render( _scene, _context_scene );
      // _renderer->Render( _ui   , _context_ui    );

      // Flip the buffers.
      _window->Flip();
    }
  }
}