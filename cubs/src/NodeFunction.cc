#include <cassert>
#include "NodeFunction.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the function node, initializing all node to null.
    */
    NodeFunction::NodeFunction()
      : _headerFunc(0),
	_declarations(0), _compoundInstr(0)
    {
    }

    /*!
    ** Destruct the function node, deleting all nodes.
    */
    NodeFunction::~NodeFunction()
    {
      delete _headerFunc;
      delete _declarations;
      delete _compoundInstr;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeFunction::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeFunction::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the declarations node.
    **
    ** @return The declaratinons node
    */
    NodeDeclarations*
    NodeFunction::getDeclarations() const
    {
      return _declarations;
    }

    /*!
    ** Get the compound instruction node.
    **
    ** @return The compound instruction node
    */
    NodeCompoundInstr*
    NodeFunction::getCompoundInstr() const
    {
      return _compoundInstr;
    }

    /*!
    ** Get the header function node.
    **
    ** @return The header function node.
    */
    NodeHeaderFunc*
    NodeFunction::getHeaderFunc() const
    {
      return _headerFunc;
    }

    /*!
    ** Set the header function node.
    **
    ** @param node The header function node
    */
    void
    NodeFunction::setHeaderFunc(NodeHeaderFunc* node)
    {
      _headerFunc = node;
    }

    /*!
    ** Set the declarations node.
    **
    ** @param node The declarations node
    */
    void
    NodeFunction::setDeclarations(NodeDeclarations* node)
    {
      _declarations = node;
    }

    /*!
    ** Set the compound instruction node.
    **
    ** @param node The coompound instruction node
    */
    void
    NodeFunction::setCompoundInstr(NodeCompoundInstr* node)
    {
      _compoundInstr = node;
    }

    /*!
    ** Get the argument node.
    **
    ** @param pos The index of wanted argument
    **
    ** @return The wanted argument.
    */
    NodeId*
    NodeFunction::getArgument(const unsigned int pos) const
    {
      assert(pos < nbArgument());
      return _args[pos];
    }

    /*!
    ** Get the number of argument.
    **
    ** @return The number of argument
    */
    unsigned int
    NodeFunction::nbArgument() const
    {
      return _args.size();
    }

    /*!
    ** Add an argument, ie an id node.
    **
    ** @param node The id node to add
    */
    void
    NodeFunction::addArgument(NodeId* node)
    {
      _args.push_back(node);
    }
  }
}
