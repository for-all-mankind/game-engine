#ifndef ICE_INPUT_H
#define ICE_INPUT_H

#include "../util/types.h"

#include <GLFW/glfw3.h>

#include <unordered_map>
#include <vector>

namespace Ice
{
  // Callback functions for
  // hooking into glfw.
  void key_callback( GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods );

  /////////////////////////////////

  typedef void (*ContextCallback)();

  /////////////////////////////////

  class InputContext
  {
  public:
    InputContext();
    ~InputContext();

    void Register( i32 key, i32 mods, ContextCallback function );
    void Call    ( i32 key, i32 mods );

  private:
    std::unordered_map<u64, ContextCallback> _functions;
  };

  /////////////////////////////////

  class InputController
  {
  public:
    static InputController* GetInstance();
    static void             Free();

    // Create a new context and adds it to the list.
    u32 NewContext();

    InputContext* GetContext( u32 uid );
    InputContext* GetCurrent();
    InputContext* GetGlobal ();

  private:
    InputController();
    ~InputController();

    // No copying or moving of the input class.
    InputController( const InputController&  copy ) = delete;
    InputController(       InputController&& move ) = delete;

    // No copy or move assignment of the input class.
    InputController& operator=( const InputController&  copy ) = delete;
    InputController& operator=(       InputController&& move ) = delete;

  private:
    static InputController* _instance;

    InputContext* _global;
    InputContext* _current;

    std::vector<InputContext*> _registered_contexts;
  };
}

#endif // ICE_INPUT_H