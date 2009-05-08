#include "NodeId.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the node id, setting it's not a declaration by default,
    ** and initializing referenced id node to null.
    */
    NodeId::NodeId()
      : _isDecl(false), _ref(0)
    {
    }

    /*!
    ** Destruct the id node, without deleting referenced id node,
    ** because it's just a reference.
    */
    NodeId::~NodeId()
    {
      // Do not delete _ref here, it's just a pointer
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeId::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeId::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the string id.
    **
    ** @return The string id
    */
    const std::string&
    NodeId::getId() const
    {
      return _id;
    }

    /*!
    ** Set the string id.
    **
    ** @param id The string id
    */
    void
    NodeId::setId(const std::string& id)
    {
      _id = id;
    }

    /*!
    ** Check if it's a declaration.
    **
    ** @return If it's a declaration
    */
    bool
    NodeId::isDeclaration() const
    {
      return _isDecl;
    }

    /*!
    ** Set if it's a declaration.
    **
    ** @param isDecl If it's a declration
    */
    void
    NodeId::setDeclaration(bool isDecl)
    {
      _isDecl = isDecl;
    }

    /*!
    ** Get the referenced node id.
    **
    ** @return The referenced node id
    */
    NodeId*
    NodeId::getRef() const
    {
      return _ref;
    }

    /*!
    ** Set the referenced id node.
    **
    ** @param node The referenced id node
    */
    void
    NodeId::setRef(NodeId* node)
    {
      _ref = node;
    }
  }
}
