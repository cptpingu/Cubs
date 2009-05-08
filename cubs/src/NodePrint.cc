#include "NodePrint.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the print node, initializing expression node to null.
     */
    NodePrint::NodePrint()
      : _expr(0)
    {
    }

    /*!
    ** Destruct the print node.
     */
    NodePrint::~NodePrint()
    {
      delete _expr;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodePrint::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodePrint::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the expression node.
    **
    ** @return The expression node
    */
    NodeExpression*
    NodePrint::getExpr() const
    {
      return _expr;
    }

    /*!
    ** Set the expression node.
    **
    ** @param node The expression node
    */
    void
    NodePrint::setExpr(NodeExpression* node)
    {
      _expr = node;
    }
  }
}
