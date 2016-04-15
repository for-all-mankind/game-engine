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

  void Node::Update()
  {
    for ( Component* c : _components )
      c->Update();
  }

  void Node::Render() const
  {
    for ( Component* c : _components )
      c->Render();
  }
}