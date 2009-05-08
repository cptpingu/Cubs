#include "NodeType.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the type node.
    */
    NodeType::NodeType()
    {
    }

    /*!
    ** Destruct the type node.
     */
    NodeType::~NodeType()
    {
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeType::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeType::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the string type of the node.
    **
    ** @return The type
    */
    const std::string&
    NodeType::getType() const
    {
      return _type;
    }

    /*!
    ** Set the the string type of the node.
    **
    ** @param type The type
    */
    void
    NodeType::setType(const std::string& type)
    {
      _type = type;
    }
  }
}
