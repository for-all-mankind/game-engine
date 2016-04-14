#include "window.h"

namespace Ice
{

  Window::Window( const WindowConfig&& cfg )
    : _closed( false )
  {
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE    , 8  );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE  , 8  );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE   , 8  );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE  , 8  );
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE , 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1  );

    // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    // SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE );

    _window = SDL_CreateWindow( cfg.title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                cfg.width, cfg.height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );

    // TODO:
    // throw exceptions when we encounter errors.
    if ( !_window )
    {
      SDL_Log( SDL_GetError() );
      exit( 1 );
    }

    _context = SDL_GL_CreateContext( _window );

    if ( !_context )
    {
      SDL_Log( SDL_GetError() );
      exit( 1 );
    }

    if ( glewInit() != GLEW_OK )
    {
      SDL_Log( "Failed to initialise GLEW." );
      exit( 1 );
    }
  }

  Window::~Window()
  {
    SDL_GL_DeleteContext( _context );
    SDL_DestroyWindow   ( _window  );
  }

  void Window::Clear()
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }

  void Window::Update()
  {
    SDL_GL_SwapWindow( _window );
  }

  bool Window::IsOpen() const
  {
    return !_closed;
  }

  void Window::Close()
  {
    _closed = true;
  }

  void Window::HandleEvents( const SDL_Event& e )
  {
    switch( e.window.event )
    {
      default:
        break;
    }
  }

}