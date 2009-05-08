#include "NodeExpression.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the expression node, settings all node to null.
    */
    NodeExpression::NodeExpression()
      : _op(0)
    {
    }

    /*!
    ** Destruct the node expression
    */
    NodeExpression::~NodeExpression()
    {
      delete _op;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeExpression::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeExpression::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the operation node.
    **
    ** @return The operation node
    */
    NodeOperation*
    NodeExpression::getOperation() const
    {
      return _op;
    }

    /*!
    ** Set the operation node.
    **
    ** @param op The operation node
    */
    void
    NodeExpression::setOperation(NodeOperation* op)
    {
      _op = op;
    }
  }
}
