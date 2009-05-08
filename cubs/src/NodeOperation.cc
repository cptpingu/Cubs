#include "NodeOperation.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the operation node, initializing all factor nodes
    ** to null, and setting operation type to NONE.
     */
    NodeOperation::NodeOperation()
      : _leftFactor(0), _rightFactor(0), _opType(Operator::NONE)
    {
    }

    /*!
    ** Delete all factor nodes.
     */
    NodeOperation::~NodeOperation()
    {
      delete _leftFactor;
      delete _rightFactor;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeOperation::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeOperation::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the left factor node.
    **
    ** @return The left factor node
    */
    NodeFactor*
    NodeOperation::getLeftFactor() const
    {
      return _leftFactor;
    }

    /*!
    ** Get the right factor node.
    **
    ** @return The right factor node
    */
    NodeFactor*
    NodeOperation::getRightFactor() const
    {
      return _rightFactor;
    }

    /*!
    ** Set the left factor node.
    **
    ** @param node The left factor node
    */
    void
    NodeOperation::setLeftFactor(NodeFactor* node)
    {
      _leftFactor = node;
    }

    /*!
    ** Set the right factor node.
    **
    ** @param node The right factor node
    */
    void
    NodeOperation::setRightFactor(NodeFactor* node)
    {
      _rightFactor = node;
    }

    /*!
    ** Get the operation type.
    **
    ** @return The operation type
    */
    Operator::type
    NodeOperation::getOpType() const
    {
      return _opType;
    }

    /*!
    ** Set the operation type.
    **
    ** @param opType The operation type
    */
    void
    NodeOperation::setOpType(Operator::type opType)
    {
      _opType = opType;
    }
  }
}
