#include "NodeDeclarations.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the declarations node, initializing all nodes.
    */
    NodeDeclarations::NodeDeclarations()
      : _decl(0), _decls(0)
    {
    }

    /*!
    ** Destruct the declarations node, deleting all nodes.
    */
    NodeDeclarations::~NodeDeclarations()
    {
      delete _decl;
      delete _decls;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeDeclarations::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeDeclarations::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the declaration node.
    **
    ** @return The declaration node
    */
    NodeDeclaration*
    NodeDeclarations::getDeclaration() const
    {
      return _decl;
    }

    /*!
    ** Get the declarations node.
    **
    ** @return The declarations node
    */
    NodeDeclarations*
    NodeDeclarations::getDeclarations() const
    {
      return _decls;
    }

    /*!
    ** Set the declaration node.
    **
    ** @param node The declaration node
    */
    void
    NodeDeclarations::setDeclaration(NodeDeclaration* node)
    {
      _decl = node;
    }

    /*!
    ** Set the declarations node.
    **
    ** @param node The declarations node
    */
    void
    NodeDeclarations::setDeclarations(NodeDeclarations* node)
    {
      _decls = node;
    }
  }
}
