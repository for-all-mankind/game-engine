#include "engine.h"

#include <iostream>

namespace Ice
{
  Engine::Engine()
   : _window( nullptr )
  {
    SDL_Init( SDL_INIT_VIDEO
            | SDL_INIT_EVENTS
            | SDL_INIT_AUDIO
            | SDL_INIT_TIMER );
  }

  Engine::~Engine()
  {
    if ( _window != nullptr )
      delete _window;

    SDL_Quit();
  }

  bool Engine::InitWindow( const WindowConfig&& cfg )
  {
    // TODO:
    // Use a try catch here once the window's constructor
    // throws errors on failure.

    _window = new Window{ std::move( cfg ) };

    // The rendering engine will be initialised here too,
    // since OpenGL can't do anything until the context is
    // created and that is handled by the window.

    return true;
  }

  void Engine::Run()
  {
    // The window hasn't been initialised yet, so
    // we can't do anything.
    if ( _window == nullptr )
    {
      std::cout << "The window is not initialised" << std::endl;
      return;
    }

    SDL_Event e;

    while ( _window->IsOpen() )
    {
      _window->Clear();

      while ( SDL_PollEvent( &e ) )
      {
        switch( e.type )
        {
          case SDL_QUIT:
            _window->Close();
            break;

          case SDL_WINDOWEVENT:
            _window->HandleEvents( e );
            break;

          default:
            // TODO: pass event to the input controller.
            break;
        }
      }

      // TODO:
      // Update entities.
      // Render scene.

      _window->Update();
    }
  }
}