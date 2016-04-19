#include <Ice/Input.hpp>

namespace Ice
{
  void cursor_input( GLFWwindow* window, f64 xpos, f64 ypos )
  {

  }

  void cursor_enter( GLFWwindow* window, i32 entered )
  {

  }

  void button_input( GLFWwindow* window, i32 button, i32 action, i32 mods )
  {

  }

  void scroll_input( GLFWwindow* window, f64 xoffset, f64 yoffset )
  {

  }

  void key_input( GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods )
  {
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE )
      glfwSetWindowShouldClose( window, true );
  }

  void text_input( GLFWwindow* window, u32 codepoint, i32 mods )
  {

  }

  /////////////////////////////////

  Input* Input::_instance = nullptr;

  Input::Input()
  {

  }

  Input* Input::GetInstance()
  {
    if ( _instance == nullptr )
      _instance = new Input();

    return _instance;
  }

  void Input::Free()
  {
    if ( _instance == nullptr )
      delete _instance;
  }

  void Input::Update()
  {

  }

  bool Input::KeyPressed ( i32 key ) const { return false; }
  bool Input::KeyReleased( i32 key ) const { return false; }
  bool Input::KeyHeld    ( i32 key ) const { return false; }

  bool Input::ButtonPressed ( i32 button ) const { return false; }
  bool Input::ButtonReleased( i32 button ) const { return false; }
  bool Input::ButtonHeld    ( i32 button ) const { return false; }

  void Input::GetMousePosition( i32* x, i32* y ) const
  {

  }

  void Input::SetKey( i32 key, bool set )
  {

  }

  void Input::SetButton( i32 button, bool set )
  {

  }
}