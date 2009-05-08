#include "NodeFunctions.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the functions node, initializing all nodes to null.
    */
    NodeFunctions::NodeFunctions()
      : _funcs(0), _func(0)
    {
    }

    /*!
    ** Destruct the functions node, deleting all nodes.
    */
    NodeFunctions::~NodeFunctions()
    {
      delete _funcs;
      delete _func;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeFunctions::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeFunctions::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the functions node.
    **
    ** @return The functions node
    */
    NodeFunctions*
    NodeFunctions::getFuncs() const
    {
      return _funcs;
    }

    /*!
    ** Get the functions node.
    **
    ** @return The functions node
    */
    NodeFunction*
    NodeFunctions::getFunc() const
    {
      return _func;
    }

    /*!
    ** Set the functions node.
    **
    ** @param node The functions node
    */
    void
    NodeFunctions::setFuncs(NodeFunctions* node)
    {
      _funcs = node;
    }

    /*!
    ** Ste the function node.
    **
    ** @param node The function node.
    */
    void
    NodeFunctions::setFunc(NodeFunction* node)
    {
      _func = node;
    }
  }
}
