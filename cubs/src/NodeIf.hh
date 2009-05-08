#ifndef NODEIF_HH_
# define NODEIF_HH_

# include "Node.hh"
# include "NodeCompoundInstr.hh"
# include "NodeExpressions.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** if ::= "if" expression "then" compound_instruction
    **      | "if" expression "then" compound_instruction "else" compound_instruction
    */
    class NodeIf : public Node
    {
    public:
      NodeIf();
      virtual ~NodeIf();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeExpression* getCond() const;
      NodeCompoundInstr* getBodyExprs() const;
      NodeCompoundInstr* getElseExprs() const;
      void setCond(NodeExpression* node);
      void setBodyExprs(NodeCompoundInstr* node);
      void setElseExprs(NodeCompoundInstr* node);

    private:
      NodeExpression*		_cond;
      NodeCompoundInstr*	_bodyExprs;
      NodeCompoundInstr*	_elseExprs;
    };
  }
}

#endif /* !NODEIF_HH_ */
