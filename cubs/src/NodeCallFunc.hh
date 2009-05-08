#ifndef NODECALLFUNC_HH_
# define NODECALLFUNC_HH_

# include "TypedNode.hh"
# include "NodeIdFunc.hh"
# include "NodeExpression.hh"
# include "NodeExpressions.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** call_func ::= id "(" ")"
    **             | id "(" expressions ")"
    */
    class NodeCallFunc : public TypedNode
    {
    public:
      NodeCallFunc();
      virtual ~NodeCallFunc();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeIdFunc* getId() const;
      NodeExpressions* getExprs() const;
      void setId(NodeIdFunc* node);
      void setExprs(NodeExpressions* node);

    public:
      NodeExpression* getArgument(const unsigned int pos) const;
      unsigned int nbArgument() const;
      void addArgument(NodeExpression* node);

    private:
      NodeIdFunc*			_id;
      NodeExpressions*			_exprs;
      std::vector<NodeExpression*>	_args;
    };
  }
}

#endif /* !NODECALLFUNC_HH_ */
