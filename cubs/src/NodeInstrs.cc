#include "NodeInstrs.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the instructions node, initializing
    ** instructions and instruction to null.
    */
    NodeInstrs::NodeInstrs()
      : _instrs(0), _instr(0)
    {
    }

    /*!
    ** Destruct the instructions node.
    */
    NodeInstrs::~NodeInstrs()
    {
      delete _instrs;
      delete _instr;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeInstrs::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeInstrs::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the instructions node.
    **
    ** @return The instructions node
    */
    NodeInstrs*
    NodeInstrs::getInstrs() const
    {
      return _instrs;
    }

    /*!
    ** Get the instruction node.
    **
    ** @return The instruction node.
    */
    NodeInstr*
    NodeInstrs::getInstr() const
    {
      return _instr;
    }

    /*!
    ** Set the instructions node.
    **
    ** @param node The instructions node
    */
    void
    NodeInstrs::setInstrs(NodeInstrs* node)
    {
      _instrs = node;
    }

    /*!
    ** Set the instruction node.
    **
    ** @param node The instruction node
    */
    void
    NodeInstrs::setInstr(NodeInstr* node)
    {
      _instr = node;
    }
  }
}
