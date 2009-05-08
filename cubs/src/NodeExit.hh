#ifndef NODEEXIT_HH_
# define NODEEXIT_HH_

# include "TypedNode.hh"
# include "NodeExpression.hh"
# include "NodeFunction.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** exit ::= "exit" expression
    */
    class NodeExit : public TypedNode
    {
    public:
      NodeExit();
      virtual ~NodeExit();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeExpression* getExpr() const;
      void setExpr(NodeExpression* node);

    private:
      NodeExpression*	_expr;
    };
  }
}

#endif /* !NODEEXIT_HH_ */
