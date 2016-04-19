#include <Ice/Node.hpp>

namespace Ice
{
  NodeRef::NodeRef()
    : NodeRef( nullptr )
  {}

  NodeRef::NodeRef( NodeRef* parent )
    : _parent( parent  )
    , _node  ( nullptr )
  {}

  NodeRef::~NodeRef()
  {
    if ( _node != nullptr )
      delete _node;
  }

  void NodeRef::AddNode( NodeRef* node )
  {
    _children.push_back( node );
  }

  void NodeRef::DetachNode( NodeRef* node )
  {

  }

  void NodeRef::RemoveNode( NodeRef* node )
  {

  }

  Node* NodeRef::GetNode()
  {
    return _node;
  }

  void NodeRef::Show()
  {
    _is_hidden = false;
  }

  void NodeRef::Hide()
  {
    _is_hidden = true;
  }

  bool NodeRef::IsHidden() const
  {
    return _is_hidden;
  }

  void NodeRef::Update( f32 delta )
  {
    if ( _node != nullptr )
      _node->Update( delta );

    for ( NodeRef* n : _children )
      n->Update( delta );
  }

  void NodeRef::Render() const
  {
    if ( _is_hidden )
      return;

    if ( _node != nullptr )
      _node->Render();

    for ( NodeRef* n : _children )
      n->Render();
  }
}