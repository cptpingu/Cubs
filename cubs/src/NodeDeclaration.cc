#include "NodeDeclaration.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the declaration node, initializing all nodes.
    */
    NodeDeclaration::NodeDeclaration()
      : _body(0)
    {
    }

    /*!
    ** Destruct the declaration node, initializing all nodes.
    */
    NodeDeclaration::~NodeDeclaration()
    {
      delete _body;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeDeclaration::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeDeclaration::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the declaration body node.
    **
    ** @return The declaration body node
    */
    NodeDeclarationBody*
    NodeDeclaration::getBody() const
    {
      return _body;
    }

    /*!
    ** Set the declaration body node.
    **
    ** @return The declaration body node
    */
    void
    NodeDeclaration::setBody(NodeDeclarationBody* node)
    {
      _body = node;
    }
  }
}
