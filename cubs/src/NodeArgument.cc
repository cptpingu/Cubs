#include "NodeArgument.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the argument node, initializing all nodes to null.
    */
    NodeArgument::NodeArgument()
      : _declarationBody(0), _arguments(0)
    {
    }

    /*!
    ** Destruct the argument node, deleting all nodes.
    */
    NodeArgument::~NodeArgument()
    {
      delete _declarationBody;
      delete _arguments;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeArgument::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeArgument::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the declaration body node.
    **
    ** @return The declaration body node
    */
    NodeDeclarationBody*
    NodeArgument::getDeclarationBody() const
    {
      return _declarationBody;
    }

    /*!
    ** Get the arguments node.
    **
    ** @return The arguments node
    */
    NodeArguments*
    NodeArgument::getArguments() const
    {
      return _arguments;
    }

    /*!
    ** Set the declaration body node.
    **
    ** @return The declaration body node
    */
    void
    NodeArgument::setDeclarationBody(NodeDeclarationBody* node)
    {
      _declarationBody = node;
    }

    /*!
    ** Set the arguments node.
    **
    ** @return The arguments node
    */
    void
    NodeArgument::setArguments(NodeArguments* node)
    {
      _arguments = node;
    }
  }
}
