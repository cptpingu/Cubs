#include "NodeReturn.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the return node.
    */
    NodeReturn::NodeReturn()
      : _expr(0)
    {
    }

    /*!
    ** Destruct the return node.
    */
    NodeReturn::~NodeReturn()
    {
      delete _expr;
    }

    /*!
    ** Accept a classic visitor
    **
    ** @param visitor The visitor
    */
    void
    NodeReturn::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor
    **
    ** @param visitor The visitor
    */
    void
    NodeReturn::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the expression node.
    **
    ** @return The expression
    */
    NodeExpression*
    NodeReturn::getExpr() const
    {
      return _expr;
    }

    /*!
    ** Set the expression node.
    **
    ** @param node The expression
    */
    void
    NodeReturn::setExpr(NodeExpression* node)
    {
      _expr = node;
    }

    /*!
    ** Get the associated function node.
    **
    ** @return The associated function node
    */
    NodeFunction*
    NodeReturn::getRefFunc() const
    {
      return _linkedFunction;
    }

    /*!
    ** Set the associated function node.
    **
    ** @param node The associated function node
    */
    void
    NodeReturn::setRefFunc(NodeFunction* node)
    {
      _linkedFunction = node;
    }
  }
}
