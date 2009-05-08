#include <cassert>
#include "NodeCallFunc.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the call function node, initializing all nodes to null.
    */
    NodeCallFunc::NodeCallFunc()
      : _id(0), _exprs(0)
    {
    }

    /*!
    ** Destruct the call function node, deleting all nodes.
    */
    NodeCallFunc::~NodeCallFunc()
    {
      delete _id;
      delete _exprs;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeCallFunc::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeCallFunc::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the function id node.
    **
    ** @return The function id node
    */
    NodeIdFunc*
    NodeCallFunc::getId() const
    {
      return _id;
    }

    /*!
    ** Get the expressions node.
    **
    ** @return The expressions node
    */
    NodeExpressions*
    NodeCallFunc::getExprs() const
    {
      return _exprs;
    }

    /*!
    ** Set the function id node.
    **
    ** @return The function id node
    */
    void
    NodeCallFunc::setId(NodeIdFunc* node)
    {
      _id = node;
    }

    /*!
    ** Set the expressions node.
    **
    ** @return The expressions node
    */
    void
    NodeCallFunc::setExprs(NodeExpressions* node)
    {
      _exprs = node;
    }

    /*!
    ** Get the argument node.
    **
    ** @param pos Wanted argument node.
    **
    ** @return The wanted argument node
    */
    NodeExpression*
    NodeCallFunc::getArgument(const unsigned int pos) const
    {
      assert(pos < nbArgument());
      return _args[pos];
    }

    /*!
    ** Get the number of argument.
    **
    ** @return The number of argument
    */
    unsigned int
    NodeCallFunc::nbArgument() const
    {
      return _args.size();
    }

    /*!
    ** Add a new argument.
    **
    ** @param node An expression node to add.
    */
    void
    NodeCallFunc::addArgument(NodeExpression* node)
    {
      _args.push_back(node);
    }
  }
}
