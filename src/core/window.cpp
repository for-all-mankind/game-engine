#include "window.h"
#include "../input/input.h"

#include <iostream>

namespace Ice
{
  static void on_window_resize( GLFWwindow* window, i32 width, i32 height )
  {
    Window::SetSize( width, height );

    i32 buffer_width;
    i32 buffer_height;

    glfwGetFramebufferSize( window, &buffer_width, &buffer_height );

    glViewport( 0, 0, buffer_width, buffer_height );
  }

  /////////////////////////////////

  u32 Window::_width  = 600;
  u32 Window::_height = 800;

  Window::Window( const WindowConfig&& cfg )
    : _window( nullptr )
  {
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE       , GLFW_OPENGL_CORE_PROFILE );

    _title      = cfg.title;
    _width      = cfg.width;
    _height     = cfg.height;
    _fullscreen = cfg.fullscreen;

    CreateWindow();

    // TODO:
    // throw exceptions when we encounter errors.
    if ( _window == nullptr )
    {
      std::cout << "Failed to create a window." << std::endl;
      glfwTerminate();
      exit( EXIT_FAILURE );
    }

    glewExperimental = GL_TRUE;
    if ( glewInit() != GLEW_OK )
    {
      std::cout << "Failed to initialise GLEW." << std::endl;
      exit( EXIT_FAILURE );
    }
  }

  Window::~Window()
  {
    glfwDestroyWindow( _window );
  }

  void Window::Update()
  {
    glfwPollEvents();

    // Switch to fullscreen mode.
    if ( glfwGetKey( _window, GLFW_KEY_F11 ) )
    {
      _fullscreen = !_fullscreen;

      CreateWindow();

      if ( _window == nullptr )
      {
        std::cout << "Failed to switch window mode." << std::endl;
        glfwTerminate();
        exit( EXIT_FAILURE );
      }
    }
  }

  void Window::Flip()
  {
    glfwSwapBuffers( _window );
  }

  bool Window::IsOpen() const
  {
    return !glfwWindowShouldClose( _window );
  }

  void Window::CreateWindow()
  {
    GLFWwindow*  new_window = nullptr;
    GLFWmonitor* primary    = nullptr;

    i32 width  = _width;
    i32 height = _height;

    if ( _fullscreen )
    {
      primary = glfwGetPrimaryMonitor();

      const GLFWvidmode* mode = glfwGetVideoMode( primary );

      width  = mode->width;
      height = mode->height;
    }

    new_window = glfwCreateWindow( width, height,
                                   _title.c_str(),
                                   primary, _window );

    if ( _window != nullptr );
      glfwDestroyWindow( _window );

    _window = new_window;

    glViewport( 0, 0, width, height );
    glfwMakeContextCurrent( _window );

    // Register callbacks
    glfwSetCursorPosCallback  ( _window, cursor_input );
    glfwSetCursorEnterCallback( _window, cursor_enter );
    glfwSetMouseButtonCallback( _window, button_input );
    glfwSetScrollCallback     ( _window, scroll_input );
    glfwSetKeyCallback        ( _window, key_input    );
    glfwSetCharModsCallback   ( _window, text_input   );

    glfwSetWindowSizeCallback( _window, on_window_resize );
  }

  void Window::SetSize( u32 width, u32 height )
  {
    _width  = width;
    _height = height;
  }

  u32 Window::GetWidth () { return _width;  }
  u32 Window::GetHeight() { return _height; }
}