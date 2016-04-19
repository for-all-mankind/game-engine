#ifndef ICE_INPUT_H
#define ICE_INPUT_H

#include <Ice/Common/Types.hpp>
#include <Ice/Common/NonCopy.hpp>
#include <Ice/Common/OpenGL.hpp>

#include <vector>

namespace Ice
{
  // Callback functions for hooking into glfw.
  void cursor_input( GLFWwindow* window, f64 xpos, f64 ypos );
  void cursor_enter( GLFWwindow* window, i32 entered );
  void button_input( GLFWwindow* window, i32 button, i32 action, i32 mods );
  void scroll_input( GLFWwindow* window, f64 xoffset, f64 yoffset );
  void key_input   ( GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods );
  void text_input  ( GLFWwindow* window, u32 codepoint, i32 mods );
  void path_drop   ( GLFWwindow* window, i32 count, const char** paths );

  // glfwGetClipboardstd::string();
  // glfwSetClipboardstd::string();

  /////////////////////////////////

  const i32 MAX_KEYS    = 1024;
  const i32 MAX_BUTTONS = 32;

  /////////////////////////////////

  class Input : public Common::NonCopyable
  {
  public:
    static Input* GetInstance();
    static void          Free();

    void Update();

    bool KeyPressed ( i32 key ) const;
    bool KeyReleased( i32 key ) const;
    bool KeyHeld    ( i32 key ) const;

    bool ButtonPressed ( i32 button ) const;
    bool ButtonReleased( i32 button ) const;
    bool ButtonHeld    ( i32 button ) const;

    void GetMousePosition( i32* x, i32* y ) const;

    void SetKey   ( i32 key   , bool set );
    void SetButton( i32 button, bool set );

  private:
    Input();

  private:
    // bool

    static Input* _instance;
  };
}

#endif // ICE_INPUT_H