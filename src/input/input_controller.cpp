#include "input.h"

namespace Ice
{
  InputController* InputController::_instance = nullptr;

  InputController::InputController()
  {
    _global = new InputContext{};
  }

  InputController::~InputController()
  {
    for ( InputContext* i : _registered_contexts )
      delete i;

    delete _global;
  }

  InputController* InputController::GetInstance()
  {
    if ( _instance == nullptr )
      _instance = new InputController{};

    return _instance;
  }

  void InputController::Free()
  {
    if ( _instance != nullptr )
      delete _instance;
  }

  u32 InputController::NewContext()
  {
              _registered_contexts.emplace_back( new InputContext{} );
    u32 uid = _registered_contexts.size() - 1;

    _current = _registered_contexts[ uid ];

    return uid;
  }

  InputContext* InputController::GetContext( u32 uid )
  {
    if ( uid >= _registered_contexts.size() )
      return nullptr;

    return _registered_contexts[ uid ];
  }

  InputContext* InputController::GetCurrent()
  {
    if ( _registered_contexts.size() == 0 )
      return nullptr;

    return _current;
  }

  InputContext* InputController::GetGlobal()
  {
    return _global;
  }
}