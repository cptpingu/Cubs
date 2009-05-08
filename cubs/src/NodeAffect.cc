#include "NodeAffect.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the affect node, initializing all nodes to null.
    */
    NodeAffect::NodeAffect()
      : _id(0), _expr(0)
    {
    }

    /*!
    ** Destruct the affect node, deleting all nodes.
    */
    NodeAffect::~NodeAffect()
    {
      delete _id;
      delete _expr;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeAffect::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeAffect::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the id node.
    **
    ** @return The id node.
    */
    NodeId*
    NodeAffect::getId() const
    {
      return _id;
    }

    /*!
    ** Get the expression node.
    **
    ** @return The expression node
    */
    NodeExpression*
    NodeAffect::getExpr() const
    {
      return _expr;
    }

    /*!
    ** Set the id node.
    **
    ** @return The id node.
    */
    void
    NodeAffect::setId(NodeId* node)
    {
      _id = node;
    }

    /*!
    ** Set the expression node.
    **
    ** @return The expression node
    */
    void
    NodeAffect::setExpr(NodeExpression* node)
    {
      _expr = node;
    }
  }
}
