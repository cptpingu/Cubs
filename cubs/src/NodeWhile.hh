#ifndef NODEWHILE_HH_
# define NODEWHILE_HH_

# include "Node.hh"
# include "NodeCompoundInstr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** while ::= "while" cond "do" compound_instruction
    */
    class NodeWhile : public Node
    {
    public:
      NodeWhile();
      virtual ~NodeWhile();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeExpression*	getCond() const;
      NodeCompoundInstr* getBodyExprs() const;
      void setCond(NodeExpression* node);
      void setBodyExprs(NodeCompoundInstr* node);

    private:
      NodeExpression*		_cond;
      NodeCompoundInstr*	_bodyExprs;
    };
  }
}

#endif /* !NODEWHILE_HH_ */
