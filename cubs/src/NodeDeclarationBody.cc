#include "NodeDeclarationBody.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the declaration body node, initializing all nodes.
    */
    NodeDeclarationBody::NodeDeclarationBody()
      : _ids(0), _type(0)
    {
    }

    /*!
    ** Destruct the declaration body node, deleting all nodes.
    */
    NodeDeclarationBody::~NodeDeclarationBody()
    {
      delete _ids;
      delete _type;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeDeclarationBody::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeDeclarationBody::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the ids node.
    **
    ** @return The ids node
    */
    NodeIds*
    NodeDeclarationBody::getIds() const
    {
      return _ids;
    }

    /*!
    ** Get the type node.
    **
    ** @return The type node
    */
    NodeType*
    NodeDeclarationBody::getType() const
    {
      return _type;
    }

    /*!
    ** Set the ids node.
    **
    ** @param node The ids node
    */
    void
    NodeDeclarationBody::setIds(NodeIds* node)
    {
      _ids = node;
    }

    /*!
    ** Set the type node.
    **
    ** @param nodeType The type node
    */
    void
    NodeDeclarationBody::setType(NodeType* nodeType)
    {
      _type = nodeType;
    }
  }
}
