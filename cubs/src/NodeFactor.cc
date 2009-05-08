#include "NodeFactor.hh"
#include "NodeExpression.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the node factor, initializing all nodes to null.
    */
    NodeFactor::NodeFactor()
      : _id(0),_callFunc(0),
	_number(0), _stringExpr(0),
	_expression(0), _bool(0)
    {
    }

    /*!
    ** Destruct the node factor, deleting all nodes.
    */
    NodeFactor::~NodeFactor()
    {
      delete _id;
      delete _callFunc;
      delete _number;
      delete _stringExpr;
      delete _expression;
      delete _bool;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeFactor::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeFactor::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the id node.
    **
    ** @return The id node
    */
    NodeId*
    NodeFactor::getId() const
    {
      return _id;
    }

    /*!
    ** Get the function call node.
    **
    ** @return The function call node
    */
    NodeCallFunc*
    NodeFactor::getCallFunc() const
    {
      return _callFunc;
    }

    /*!
    ** Get the number node.
    **
    ** @return The number node
    */
    NodeNumber*
    NodeFactor::getNumber() const
    {
      return _number;
    }

    /*!
    ** Get the string expression node.
    **
    ** @return The string expression node
    */
    NodeStringExpr*
    NodeFactor::getStringExpr() const
    {
      return _stringExpr;
    }

    /*!
    ** Get the boolean node.
    **
    ** @return The boolean node
    */
    NodeBoolean*
    NodeFactor::getBool() const
    {
      return _bool;
    }

    /*!
    ** Get the expression node.
    **
    ** @return The expression node
    */
    NodeExpression*
    NodeFactor::getExpression() const
    {
      return _expression;
    }

    /*!
    ** Set the id node.
    **
    ** @param id The id node
    */
    void
    NodeFactor::setId(NodeId* id)
    {
      _id = id;
    }

    /*!
    ** Set the function call node.
    **
    ** @param node The function call node
    */
    void
    NodeFactor::setCallFunc(NodeCallFunc* node)
    {
      _callFunc = node;
    }

    /*!
    ** Set the number node.
    **
    ** @param num The number node
    */
    void
    NodeFactor::setNumber(NodeNumber* num)
    {
      _number = num;
    }

    /*!
    ** Set the string expression node.
    **
    ** @param node The string expression node
    */
    void
    NodeFactor::setStringExpr(NodeStringExpr* node)
    {
      _stringExpr = node;
    }

    /*!
    ** Set the boolean node.
    **
    ** @param node The boolean node
    */
    void
    NodeFactor::setBool(NodeBoolean* node)
    {
      _bool = node;
    }

    /*!
    ** Set the expression node.
    **
    ** @param node The expression node
    */
    void
    NodeFactor::setExpression(NodeExpression* node)
    {
      _expression = node;
    }
  }
}
