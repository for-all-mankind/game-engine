#ifndef ICE_WINDOW_H
#define ICE_WINDOW_H

#include "../util/types.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>

namespace Ice
{
  struct WindowConfig
  {
    std::string title;

    u32 width;
    u32 height;
  };

  /////////////////////////////////////

  class Window
  {
  public:
    Window( const WindowConfig&& cfg );
    ~Window();

    void Clear();
    void Update();

    bool IsOpen() const;
    void Close();

    void HandleEvents( const SDL_Event& e );

  private:
    bool _closed;

    SDL_Window*   _window;
    SDL_GLContext _context;
  };
}

#endif // ICE_WINDOW_H