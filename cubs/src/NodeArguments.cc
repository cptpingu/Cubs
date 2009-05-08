#include "NodeArguments.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the arguments node, initializing all nodes to null.
    */
    NodeArguments::NodeArguments()
      : _argument(0), _arguments(0)
    {
    }

    /*!
    ** Destruct the arguments node, deleting all nodes.
    */
    NodeArguments::~NodeArguments()
    {
      delete _argument;
      delete _arguments;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeArguments::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeArguments::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the argument node.
    **
    ** @return The argument node
    */
    NodeArgument*
    NodeArguments::getArgument() const
    {
      return _argument;
    }

    /*!
    ** Get the arguments node.
    **
    ** @return The arguments node
    */
    NodeArguments*
    NodeArguments::getArguments() const
    {
      return _arguments;
    }

    /*!
    ** Set the argument node.
    **
    ** @return The argument node
    */
    void
    NodeArguments::setArgument(NodeArgument* node)
    {
      _argument = node;
    }

    /*!
    ** Set the arguments node.
    **
    ** @return The arguments node
    */
    void
    NodeArguments::setArguments(NodeArguments* node)
    {
      _arguments = node;
    }
  }
}
