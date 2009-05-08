#ifndef NODEPRINT_HH_
# define NODEPRINT_HH_

# include "Node.hh"
# include "NodeExpression.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** print ::= "print" "(" expression ")" // builtin
    */
    class NodePrint : public Node
    {
    public:
      NodePrint();
      virtual ~NodePrint();
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

#endif /* !NODEPRINT_HH_ */
