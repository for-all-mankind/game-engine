#ifndef ICE_COMPONENT_H
#define ICE_COMPONENT_H

namespace Ice
{
  class Node;

  class Component
  {
  public:
    virtual void Update() = 0;
    virtual void Render() = 0;

  protected:
    Node* _node;
  };
}

#endif // ICE_COMPONENT_H