#ifndef ICE_COMPONENT_H
#define ICE_COMPONENT_H

#include "node.h"

namespace Ice
{
  class Component
  {
  public:
    virtual ~Component() {}

    virtual void Update( f32 delta ) = 0;
    virtual void Render() const = 0;

  protected:
    Node* _node;
  };
}

#endif // ICE_COMPONENT_H