#ifndef NODECOMPOUNDINSTR_HH_
# define NODECOMPOUNDINSTR_HH_

# include "Node.hh"
# include "NodeInstrs.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** compound_instruction ::= "begin" "end"
    **	                      | "begin" instructions "end"
    **
    */
    class NodeCompoundInstr : public Node
    {
    public:
      NodeCompoundInstr();
      virtual ~NodeCompoundInstr();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeInstrs* getInstrs() const;
      void setInstrs(NodeInstrs* node);

    private:
      NodeInstrs*	_instrs;
    };
  }
}

#endif /* !NODECOMPOUNDINSTR_HH_ */
