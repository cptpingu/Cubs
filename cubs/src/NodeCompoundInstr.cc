#include "NodeCompoundInstr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the compound instruction node, initializing all nodes.
    */
    NodeCompoundInstr::NodeCompoundInstr()
      : _instrs(0)
    {
    }

    /*!
    ** Destruct the compound instruction node, deleting all, nodes.
    */
    NodeCompoundInstr::~NodeCompoundInstr()
    {
      delete _instrs;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeCompoundInstr::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeCompoundInstr::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the instructions node.
    **
    ** @return The instructions node
    */
    NodeInstrs*
    NodeCompoundInstr::getInstrs() const
    {
      return _instrs;
    }

    /*!
    ** Set the instructions node.
    **
    ** @return The instructions node
    */
    void
    NodeCompoundInstr::setInstrs(NodeInstrs* node)
    {
      _instrs = node;
    }
  }
}
