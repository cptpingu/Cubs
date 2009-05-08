#include "NodeIf.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the if node, initializing all nodes to null.
    */
    NodeIf::NodeIf()
      : _cond(0), _bodyExprs(0), _elseExprs(0)
    {
    }

    /*!
    ** Destruct if node, deleting all nodes.
     */
    NodeIf::~NodeIf()
    {
      delete _cond;
      delete _bodyExprs;
      delete _elseExprs;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeIf::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeIf::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the condition node.
    **
    ** @return The condition node
    */
    NodeExpression*
    NodeIf::getCond() const
    {
      return _cond;
    }

    /*!
    ** Get the body expression node.
    **
    ** @return The body expression node
    */
    NodeCompoundInstr*
    NodeIf::getBodyExprs() const
    {
      return _bodyExprs;
    }

    /*!
    ** Get the else expression node.
    **
    ** @return The else expression node
    */
    NodeCompoundInstr*
    NodeIf::getElseExprs() const
    {
      return _elseExprs;
    }

    /*!
    ** Set the condition node.
    **
    ** @param node The condition node
    */
    void
    NodeIf::setCond(NodeExpression* node)
    {
      _cond = node;
    }

    /*!
    ** Set the body expression.
    **
    ** @param node The body expression
    */
    void
    NodeIf::setBodyExprs(NodeCompoundInstr* node)
    {
      _bodyExprs= node;
    }

    /*!
    ** Set the else expression node.
    **
    ** @param node The else expression node
    */
    void
    NodeIf::setElseExprs(NodeCompoundInstr* node)
    {
      _elseExprs = node;
    }
  }
}
