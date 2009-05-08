#include "NodeProgram.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the program node, initializing
    ** declarations, functions and instructions node to null.
    */
    NodeProgram::NodeProgram()
      : _decls(0), _funcs(0), _instrs(0)
    {
    }

    /*!
    ** Delete all own nodes.
     */
    NodeProgram::~NodeProgram()
    {
      delete _decls;
      delete _funcs;
      delete _instrs;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeProgram::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeProgram::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the declarations node.
    **
    ** @return The declarations node
    */
    NodeDeclarations*
    NodeProgram::getDecls() const
    {
      return _decls;
    }

    /*!
    ** Get the functions node.
    **
    ** @return The functions node
    */
    NodeFunctions*
    NodeProgram::getFuncs() const
    {
      return _funcs;
    }

    /*!
    ** Get the instructions node.
    **
    ** @return The instructions node
    */
    NodeCompoundInstr*
    NodeProgram::getInstrs() const
    {
      return _instrs;
    }

    /*!
    ** Set the declarations node.
    **
    ** @param node The declaration node
    */
    void
    NodeProgram::setDecls(NodeDeclarations* node)
    {
      _decls = node;
    }

    /*!
    ** Set the functions node.
    **
    ** @param node The functions node
    */
    void
    NodeProgram::setFuncs(NodeFunctions* node)
    {
      _funcs = node;
    }

    /*!
    ** Set the instructions node.
    **
    ** @param node The instructions node
    */
    void
    NodeProgram::setInstrs(NodeCompoundInstr* node)
    {
      _instrs = node;
    }
  }
}
