#include "NodeStringExpr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the string expression node.
    */
    NodeStringExpr::NodeStringExpr()
    {
    }

    /*!
    ** Destruct the string expression node.
    */
    NodeStringExpr::~NodeStringExpr()
    {
    }

    /*!
    ** Accept a classic visitor
    **
    ** @param visitor The visitor
    */
    void
    NodeStringExpr::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor
    **
    ** @param visitor The visitor
    */
    void
    NodeStringExpr::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the string expression.
    **
    ** @return The string expression
    */
    const std::string&
    NodeStringExpr::getString() const
    {
      return _stringExpr;
    }

    /*!
    ** Set the string expression as a string.
    **
    ** @param s The string expression
    */
    void
    NodeStringExpr::setString(const std::string& s)
    {
      _stringExpr = s;
    }
  }
}
