#ifndef NODERETURN_HH_
# define NODERETURN_HH_

# include "TypedNode.hh"
# include "NodeExpression.hh"
# include "NodeFunction.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** return ::= "return" expression
    */
    class NodeReturn : public TypedNode
    {
    public:
      NodeReturn();
      virtual ~NodeReturn();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeExpression* getExpr() const;
      void setExpr(NodeExpression* node);
      NodeFunction* getRefFunc() const;
      void setRefFunc(NodeFunction* node);

    private:
      NodeExpression*	_expr;
      NodeFunction*	_linkedFunction;
    };
  }
}

#endif /* !NODERETURN_HH_ */
