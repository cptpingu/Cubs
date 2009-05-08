#ifndef NODEINSTR_HH_
# define NODEINSTR_HH_

# include "Node.hh"

# include "NodeAffect.hh"
# include "NodeCompoundInstr.hh"
# include "NodeCallFunc.hh"
# include "NodeIf.hh"
# include "NodeWhile.hh"
# include "NodeReturn.hh"
# include "NodeExit.hh"
# include "NodePrint.hh"
# include "NodeRead.hh"

namespace MiniCompiler
{
  namespace AST
  {
    class NodeCompoundInstr;
    /*!
    ** instruction ::= affect
    **               | call_func
    **               | if
    **               | while
    **               | return
    **               | exit
    **               | builtin_print
    **               | builtin_get
    */
    class NodeInstr : public Node
    {
    public:
      NodeInstr();
      virtual ~NodeInstr();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeAffect* getAffect() const;
      NodeCallFunc* getCallFunc() const;
      NodeIf* getIf() const;
      NodeWhile* getWhile() const;
      NodeReturn* getReturn() const;
      NodeExit* getExit() const;
      NodePrint* getPrint() const;
      NodeRead* getRead() const;
      NodeCompoundInstr* getCompoundInstr() const;
      void setAffect(NodeAffect* node);
      void setCallFunc(NodeCallFunc* node);
      void setIf(NodeIf* node);
      void setWhile(NodeWhile* node);
      void setReturn(NodeReturn* node);
      void setExit(NodeExit* node);
      void setPrint(NodePrint* node);
      void setRead(NodeRead* node);
      void setCompoundInstr(NodeCompoundInstr* node);

    private:
      NodeAffect*		_affect;
      NodeCallFunc*		_callFunc;
      NodeCompoundInstr*	_compoundInstr;
      NodeIf*			_if;
      NodeWhile*		_while;
      NodeReturn*		_return;
      NodeExit*			_exit;
      NodePrint*		_print;
      NodeRead*			_read;
    };
  }
}

#endif /* !NODEINSTR_HH_ */
