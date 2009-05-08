#ifndef NODEEXPRESSION_HH_
# define NODEEXPRESSION_HH_

# include "TypedNode.hh"
# include "NodeOperation.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** expression ::= operation
    */
    class NodeExpression : public TypedNode
    {
    public:
      NodeExpression();
      virtual ~NodeExpression();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeOperation* getOperation() const;
      void setOperation(NodeOperation* op);

    private:
      NodeOperation*	_op;
    };
  }
}

#endif /* !NODEEXPRESSION_HH_ */
