#ifndef NODEEXPRESSIONS_HH_
# define NODEEXPRESSIONS_HH_

# include "Node.hh"

namespace MiniCompiler
{
  namespace AST
  {
    class NodeExpression;
    /*!
    ** expressions ::= expression
    **               | expression "," expressions
    */
    class NodeExpressions : public Node
    {
    public:
      NodeExpressions();
      virtual ~NodeExpressions();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeExpression* getExpr() const;
      NodeExpressions* getExprs() const;
      void setExpr(NodeExpression* node);
      void setExprs(NodeExpressions* node);

    private:
      NodeExpression*	_expr;
      NodeExpressions*	_exprs;
    };
  }
}

#endif /* !NODEEXPRESSIONS_HH_ */
