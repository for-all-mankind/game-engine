#ifndef ICE_COMPONENT_H
#define ICE_COMPONENT_H

#include <Ice/Common/Types.hpp>
#include <Ice/Node.hpp>

namespace Ice
{
  class Component
  {
  public:
    Component( Node* parent )
      : _node( parent )
    {}

    virtual ~Component() {}

    virtual void Update( f32 delta ) = 0;
    virtual void Render() const = 0;

  protected:
    Node* _node;
  };
}

#endif // ICE_COMPONENT_H