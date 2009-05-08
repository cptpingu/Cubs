#include "NodeExpressions.hh"
#include "NodeExpression.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the expressions node, initializing all nodes to null.
    */
    NodeExpressions::NodeExpressions()
      : _expr(0), _exprs(0)
    {
    }

    /*!
    ** Destruct the node expression, and delete all nodes.
    */
    NodeExpressions::~NodeExpressions()
    {
      delete _expr;
      delete _exprs;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeExpressions::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeExpressions::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the expression node.
    **
    ** @return The expression node
    */
    NodeExpression*
    NodeExpressions::getExpr() const
    {
      return _expr;
    }

    /*!
    ** Get the expressions node.
    **
    ** @return The expression node
    */
    NodeExpressions*
    NodeExpressions::getExprs() const
    {
      return _exprs;
    }

    /*!
    ** Set the expression node.
    **
    ** @param node The expression node
    */
    void
    NodeExpressions::setExpr(NodeExpression* node)
    {
      _expr = node;
    }

    /*!
    ** Set the expressions node
    **
    ** @param node The expressions node
    */
    void
    NodeExpressions::setExprs(NodeExpressions* node)
    {
      _exprs = node;
    }
  }
}
