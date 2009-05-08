#include "NodeRead.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the read node.
    */
    NodeRead::NodeRead()
      : _id(0)
    {
    }

    /*!
    ** Destruct the string expression node.
    */
    NodeRead::~NodeRead()
    {
      delete _id;
    }

    /*!
    ** Accept a classic visitor
    **
    ** @param visitor The visitor
    */
    void
    NodeRead::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor
    **
    ** @param visitor The visitor
    */
    void
    NodeRead::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the id node.
    **
    ** @return The id node
    */
    NodeId*
    NodeRead::getId() const
    {
      return _id;
    }

    /*!
    ** Set the id node.
    **
    ** @param node The id node
    */
    void
    NodeRead::setId(NodeId* node)
    {
      _id = node;
    }
  }
}
