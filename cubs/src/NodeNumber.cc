#include "NodeNumber.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the number node.
    */
    NodeNumber::NodeNumber()
    {
    }

    /*!
    ** Destruct the number node.
    */
    NodeNumber::~NodeNumber()
    {
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeNumber::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeNumber::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the number value.
    **
    ** @return The number value
    */
    int
    NodeNumber::getNumber() const
    {
      return _number;
    }

    /*!
    ** Set the number value.
    **
    ** @param nb The number value
    */
    void
    NodeNumber::setNumber(int nb)
    {
      _number = nb;
    }
  }
}
