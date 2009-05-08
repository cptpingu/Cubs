#ifndef NODEAFFECT_HH_
# define NODEAFFECT_HH_

# include "Node.hh"
# include "NodeId.hh"
# include "NodeExpression.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** affect ::= id "=" expression
    */
    class NodeAffect : public Node
    {
    public:
      NodeAffect();
      virtual ~NodeAffect();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeId* getId() const;
      NodeExpression* getExpr() const;
      void setId(NodeId* node);
      void setExpr(NodeExpression* node);

    private:
      NodeId*		_id;
      NodeExpression*	_expr;
    };
  }
}

#endif /* !NODEAFFECT_HH_ */
