#ifndef NODEFACTOR_HH_
# define NODEFACTOR_HH_

# include "TypedNode.hh"
# include "NodeId.hh"
# include "NodeCallFunc.hh"
# include "NodeNumber.hh"
# include "NodeStringExpr.hh"
# include "NodeBoolean.hh"

namespace MiniCompiler
{
  namespace AST
  {
    class NodeExpression;
    /*!
    ** factor ::= id
    **          | call_func
    **          | number
    **          | stringexpr
    **          | boolean
    **          | "(" expression ")"
    */
    class NodeFactor : public TypedNode
    {
    public:
      NodeFactor();
      virtual ~NodeFactor();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeId* getId() const;
      NodeCallFunc* getCallFunc() const;
      NodeNumber* getNumber() const;
      NodeStringExpr* getStringExpr() const;
      NodeBoolean* getBool() const;
      NodeExpression* getExpression() const;
      void setId(NodeId* id);
      void setCallFunc(NodeCallFunc* node);
      void setNumber(NodeNumber* num);
      void setStringExpr(NodeStringExpr* s);
      void setBool(NodeBoolean* s);
      void setExpression(NodeExpression* node);

    private:
      NodeId*		_id;
      NodeCallFunc*	_callFunc;
      NodeNumber*	_number;
      NodeStringExpr*	_stringExpr;
      NodeExpression*	_expression;
      NodeBoolean*	_bool;
    };
  }
}

#endif /* !NODEFACTOR_HH_ */
