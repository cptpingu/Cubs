#include "NodeHeaderFunc.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the header function node, initializing all nodes to null.
    */
    NodeHeaderFunc::NodeHeaderFunc()
      : _id(0), _type(0), _arguments(0)
    {
    }

    /*!
    ** Destruct the header function node, deleting all nodes.
    */
    NodeHeaderFunc::~NodeHeaderFunc()
    {
      delete _id;
      delete _type;
      delete _arguments;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeHeaderFunc::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeHeaderFunc::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the function id node.
    **
    ** @return The function id node
    */
    NodeIdFunc*
    NodeHeaderFunc::getId() const
    {
      return _id;
    }

    /*!
    ** Get the type node.
    **
    ** @return The type node
    */
    NodeType*
    NodeHeaderFunc::getType() const
    {
      return _type;
    }

    /*!
    ** Get the arguments node.
    **
    ** @return The arguments node
    */
    NodeArguments*
    NodeHeaderFunc::getArguments() const
    {
      return _arguments;
    }

    /*!
    ** Set the id function node.
    **
    ** @param id The id function node
    */
    void
    NodeHeaderFunc::setId(NodeIdFunc* id)
    {
      _id = id;
    }

    /*!
    ** Set the type node.
    **
    ** @param type The type node
    */
    void
    NodeHeaderFunc::setType(NodeType* type)
    {
      _type = type;
    }

    /*!
    ** Set the arguments node.
    **
    ** @param node The arguments node
    */
    void
    NodeHeaderFunc::setArguments(NodeArguments* node)
    {
      _arguments = node;
    }
  }
}
