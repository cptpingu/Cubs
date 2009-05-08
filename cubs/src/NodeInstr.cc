#include "NodeInstr.hh"
#include "NodeCompoundInstr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the instruction node, setting all nodes to null. 
    */
    NodeInstr::NodeInstr()
      : _affect(0), _callFunc(0), _compoundInstr(0),
	_if(0), _while(0), _return(0), _exit(0),
	_print(0), _read(0)
    {
    }

    /*!
    ** Destruct the instruction node, deleting all nodes.
     */
    NodeInstr::~NodeInstr()
    {
      delete _affect;
      delete _callFunc;
      delete _compoundInstr;
      delete _if;
      delete _while;
      delete _return;
      delete _exit;
      delete _print;
      delete _read;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeInstr::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeInstr::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the affect node.
    **
    ** @return The affect node
    */
    NodeAffect*
    NodeInstr::getAffect() const
    {
      return _affect;
    }

    /*!
    ** Get the call function node.
    **
    ** @return The call function node
    */
    NodeCallFunc*
    NodeInstr::getCallFunc() const
    {
      return _callFunc;
    }

    /*!
    ** Get the compound instruction node.
    **
    ** @return The compound instruction node
    */
    NodeCompoundInstr*
    NodeInstr::getCompoundInstr() const
    {
      return _compoundInstr;
    }

    /*!
    ** Get the if node.
    **
    ** @return The if node
    */
    NodeIf*
    NodeInstr::getIf() const
    {
      return _if;
    }

    /*!
    ** Get the while node.
    **
    ** @return The while node
    */
    NodeWhile*
    NodeInstr::getWhile() const
    {
      return _while;
    }

    /*!
    ** Get the return node.
    **
    ** @return The return node
    */
    NodeReturn*
    NodeInstr::getReturn() const
    {
      return _return;
    }

    /*!
    ** Get the exit node.
    **
    ** @return The exit node
    */
    NodeExit*
    NodeInstr::getExit() const
    {
      return _exit;
    }

    /*!
    ** Get the print node.
    **
    ** @return The print node
    */
    NodePrint*
    NodeInstr::getPrint() const
    {
      return _print;
    }

    /*!
    ** Get the read node.
    **
    ** @return The read node
    */
    NodeRead*
    NodeInstr::getRead() const
    {
      return _read;
    }

    /*!
    ** Set the affect node.
    **
    ** @param node The affect node
    */
    void
    NodeInstr::setAffect(NodeAffect* node)
    {
      _affect = node;
    }

    /*!
    ** Set the call function node
    **
    ** @param node The call function node
    */
    void
    NodeInstr::setCallFunc(NodeCallFunc* node)
    {
      _callFunc = node;
    }

    /*!
    ** Set the if node
    **
    ** @param node The if node
    */
    void
    NodeInstr::setIf(NodeIf* node)
    {
      _if = node;
    }

    /*!
    ** Set the while node
    **
    ** @param node The while node
    */
    void
    NodeInstr::setWhile(NodeWhile* node)
    {
      _while = node;
    }

    /*!
    ** Set the return node
    **
    ** @param node The return node
    */
    void
    NodeInstr::setReturn(NodeReturn* node)
    {
      _return = node;
    }

    /*!
    ** Set the exit node
    **
    ** @param node The exit node
    */
    void
    NodeInstr::setExit(NodeExit* node)
    {
      _exit = node;
    }

    /*!
    ** Set the print node
    **
    ** @param node The print node
    */
    void
    NodeInstr::setPrint(NodePrint* node)
    {
      _print = node;
    }

    /*!
    ** Set the read node
    **
    ** @param node The read node
    */
    void
    NodeInstr::setRead(NodeRead* node)
    {
      _read = node;
    }

    /*!
    ** Set the compound instruction node
    **
    ** @param node The compoound instruction node
    */
    void
    NodeInstr::setCompoundInstr(NodeCompoundInstr* node)
    {
      _compoundInstr = node;
    }
  }
}
