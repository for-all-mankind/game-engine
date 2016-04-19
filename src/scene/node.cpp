#include "node.h"
#include "component.h"

namespace Ice
{
  Node::Node()
  {

  }

  Node::~Node()
  {
    for ( Component* c : _components )
      delete c;
  }

  void Node::Update( f32 delta )
  {
    for ( Component* c : _components )
      c->Update( delta );
  }

  void Node::Render() const
  {
    for ( Component* c : _components )
      c->Render();
  }
}