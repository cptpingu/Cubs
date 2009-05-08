#include "NodeWhile.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct a while node.
    */
    NodeWhile::NodeWhile()
      : _cond(0), _bodyExprs(0)
    {
    }

    /*!
    ** Destruct a while node.
    */
    NodeWhile::~NodeWhile()
    {
      delete _cond;
      delete _bodyExprs;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeWhile::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeWhile::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the condition node.
    **
    ** @return The condition node
    */
    NodeExpression*
    NodeWhile::getCond() const
    {
      return _cond;
    }

    /*!
    ** Get the body expression.
    **
    ** @return The body expression
    */
    NodeCompoundInstr*
    NodeWhile::getBodyExprs() const
    {
      return _bodyExprs;
    }

    /*!
    ** Set the condition node.
    **
    ** @param node The condition node
    */
    void
    NodeWhile::setCond(NodeExpression* node)
    {
      _cond = node;
    }

    /*!
    ** Set the body expression of the while, ie a compound instruction.
    **
    ** @param node The body expression
    */
    void
    NodeWhile::setBodyExprs(NodeCompoundInstr* node)
    {
      _bodyExprs= node;
    }
  }
}
