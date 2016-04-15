#include "window.h"

#include <iostream>

namespace Ice
{
  static void temp_callback( GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods )
  {
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE )
      glfwSetWindowShouldClose( window, true );
  }

  /////////////////////////////////////

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

    if ( glewInit() != GLEW_OK )
    {
      std::cout << "Failed to initialise GLEW." << std::endl;
      exit( EXIT_FAILURE );
    }

    // Register callbacks
    glfwSetKeyCallback( _window, temp_callback );
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
    GLFWwindow* new_window = nullptr;

    if ( _fullscreen )
    {
            GLFWmonitor* primary = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode    = glfwGetVideoMode( primary );

      new_window = glfwCreateWindow( mode->width, mode->height,
                                     _title.c_str(),
                                     primary, _window );
    }
    else
    {
      new_window = glfwCreateWindow( _width, _height,
                                     _title.c_str(),
                                     nullptr, _window );
    }

    if ( _window != nullptr )
      glfwDestroyWindow( _window );

    _window = new_window;

    glfwMakeContextCurrent( _window );
  }


}