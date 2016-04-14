#ifndef ICE_NODE_H
#define ICE_NODE_H

#include "component.h"

#include <vector>
#include <memory>

namespace Ice
{
  /////////////////////////////////////
  // This is the class that

  class Node
  {
  public:
    Node();
    virtual ~Node();

    void Render();
    void Update();

  private:
    std::vector<Component*> _components;
  };

  /////////////////////////////////////
  // The NodeRef class is going to be the
  // main constituent element of the scene
  // graph. Each NodeRef owns a pointer to
  // a Node.

  class NodeRef
  {
  public:
    NodeRef();
    ~NodeRef();

    void AddNode   ( NodeRef* node );
    void DetachNode( NodeRef* node );
    void RemoveNode( NodeRef* node );

    void Show();
    void Hide();

    void Render();
    void Update();

  private:
    bool _is_hidden;

    Node*     _node;
    // Transform _transform;

    std::vector<NodeRef*> _children;
  };

  /////////////////////////////////////
  // The following nodes are pre-built
  // specialisations.

  class LightNode : public Node
  {

  };

  /////////////////////////////////////

  class SoundNode : public Node
  {

  };

  /////////////////////////////////////

  class ParticleNode : public Node
  {

  };
}

#endif // ICE_NODE_H