#include "NodeExit.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the exit node.
    */
    NodeExit::NodeExit()
      : _expr(0)
    {
    }

    /*!
    ** Destruct the exit node.
    */
    NodeExit::~NodeExit()
    {
      delete _expr;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeExit::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeExit::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the expression node.
    **
    ** @return The expression node
    */
    NodeExpression*
    NodeExit::getExpr() const
    {
      return _expr;
    }

    /*!
    ** Set the expression node.
    **
    ** @param node The expression node
    */
    void
    NodeExit::setExpr(NodeExpression* node)
    {
      _expr = node;
    }
  }
}
