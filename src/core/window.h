#ifndef ICE_WINDOW_H
#define ICE_WINDOW_H

#include "../util/types.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Ice
{
  struct WindowConfig
  {
    std::string title;

    u32 width;
    u32 height;

    bool fullscreen;
  };

  /////////////////////////////////////

  class Window
  {
  public:
    Window( const WindowConfig&& cfg );
    ~Window();

    void Update();
    void Flip();

    bool IsOpen() const;
    void Close();

  private:
    void CreateWindow();

  private:
    bool _fullscreen;
    u32  _width;
    u32  _height;

    std::string _title;
    GLFWwindow* _window;
  };
}

#endif // ICE_WINDOW_H