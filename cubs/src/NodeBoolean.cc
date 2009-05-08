#include "NodeBoolean.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the boolean node, initializing value to false
    */
    NodeBoolean::NodeBoolean()
      : _bool(false)
    {
    }

    /*!
    ** Destruct the call function node.
    */
    NodeBoolean::~NodeBoolean()
    {
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeBoolean::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeBoolean::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the boolean node.
    **
    ** @return The boolean node
    */
    bool
    NodeBoolean::getBool() const
    {
      return _bool;
    }

    /*!
    ** Set the boolean node.
    **
    ** @param b The boolean node
    */
    void
    NodeBoolean::setBool(const bool b)
    {
      _bool = b;
    }
  }
}
