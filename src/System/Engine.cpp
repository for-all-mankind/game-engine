#include <Ice/Common/Common.hpp>
#include <Ice/Common/File.hpp>
#include <Ice/Common/OpenGL.hpp>

#include <Ice/System/Engine.hpp>
#include <Ice/Maths/Maths.hpp>

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

    // Clean up the input system.
    // Input::Free();

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
    cfg.title      = "Anthropocene: The Age of Mankind";
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

    // _camera_current = &_camera_debug;

    // TODO:
    // Make these configurable inside the game.
    f32 aspect_ratio  = static_cast<f32>( cfg.width  )
                      / static_cast<f32>( cfg.height );

    _context_scene.projection = perspective( Constants::Tau, aspect_ratio, 0.1f, 100.0f );
    _context_scene.wire_frame = false;
    _context_scene.has_depth  = true;

    _context_ui.projection = orthographic( -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f );
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

    // The renderer isn't initialised, so we must stop.
    if ( _renderer == nullptr )
    {
      std::cout << "The renderer is not initialised." << std::endl;
      return;
    }

    while ( _window->IsOpen() )
    {
      // Get delta time.
      // f64 time_delta = _clock.DeltaTime();

      // Clear the screen
      _renderer->Clear();

      _window->Update();

      if ( _tick_counter.Update() )
        std::cout << "tps: " << _tick_counter.TickRate() << std::endl;

      // Update the key states
      // Input::GetInstance()->Update();

      // Update everything.
      // _scene.Update( time_delta );
      // _ui   .Update( time_delta );

      // Render everything.
      _renderer->Render( /*_scene,*/ _context_scene/*, _camera_current*/ );
      // _renderer->Render( _ui   , _context_ui   , _camera_current );

      // Flip the buffers.
      _window->Flip();
    }
  }
}