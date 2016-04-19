#ifndef ICE_NODE_H
#define ICE_NODE_H

#include <Ice/Common/Types.hpp>
#include <Ice/Transform.hpp>

#include <vector>

namespace Ice
{
  // Defined in "component.h"
  class Component;

  /////////////////////////////////
  // This is the class that

  class Node
  {
  public:
    Node();
    virtual ~Node();

    void Update( f32 delta );
    void Render() const;

  private:
    std::vector<Component*> _components;
  };

  /////////////////////////////////
  // The NodeRef class is going to be the
  // main constituent element of the scene
  // graph. Each NodeRef owns a pointer to
  // a Node.

  class NodeRef
  {
  public:
    NodeRef();
    NodeRef( NodeRef* parent );
    ~NodeRef();

    void AddNode   ( NodeRef* node );
    void DetachNode( NodeRef* node );
    void RemoveNode( NodeRef* node );

    Node* GetNode();

    void Show();
    void Hide();

    bool IsHidden() const;

    void Update( f32 delta );
    void Render() const;

  private:
    bool _is_hidden;

    NodeRef*  _parent;
    Node*     _node;
    Transform _transform;

    std::vector<NodeRef*> _children;
  };

  /////////////////////////////////
  // The following nodes are pre-built
  // specialisations.

  class LightNode : public Node
  {

  private:

  };

  /////////////////////////////////

  class SoundNode : public Node
  {

  };

  /////////////////////////////////

  class ParticleNode : public Node
  {

  };
}

#endif // ICE_NODE_H