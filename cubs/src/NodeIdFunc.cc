#include "NodeIdFunc.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the id function node, initializing all nodes to null.
    */
    NodeIdFunc::NodeIdFunc()
      : _isDecl(false), _ref(0)
    {
    }

    /*!
    ** Destrcuct the id function.
    */
    NodeIdFunc::~NodeIdFunc()
    {
      // Do not delete _ref here, it's just a pointer
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeIdFunc::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeIdFunc::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the string id node.
    **
    ** @return The string id node
    */
    const std::string&
    NodeIdFunc::getId() const
    {
      return _id;
    }

    /*!
    ** Set the string id.
    **
    ** @param id The string id
    */
    void
    NodeIdFunc::setId(const std::string& id)
    {
      _id = id;
    }

    /*!
    ** Check if node is a declaration.
    **
    ** @return If it's a declaration.
    */
    bool
    NodeIdFunc::isDeclaration() const
    {
      return _isDecl;
    }

    /*!
    ** Set if declaration node is a declaration.
    **
    ** @param isDecl If it's a declaration
    */
    void
    NodeIdFunc::setDeclaration(bool isDecl)
    {
      _isDecl = isDecl;
    }

    /*!
    ** Get the referenced function node.
    **
    ** @return The referenced function node
    */
    NodeFunction*
    NodeIdFunc::getRef() const
    {
      return _ref;
    }

    /*!
    ** Set the reference function node.
    **
    ** @param node The reference function node.
    */
    void
    NodeIdFunc::setRef(NodeFunction* node)
    {
      _ref = node;
    }
  }
}
