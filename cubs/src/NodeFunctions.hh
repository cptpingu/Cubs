#ifndef NODEFUNCTIONS_HH_
# define NODEFUNCTIONS_HH_

# include "Node.hh"
# include "NodeFunction.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** funcs ::= func
    **         | func funcs
    */
    class NodeFunctions : public Node
    {
    public:
      NodeFunctions();
      virtual ~NodeFunctions();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeFunctions* getFuncs() const;
      NodeFunction* getFunc() const;
      void setFuncs(NodeFunctions* node);
      void setFunc(NodeFunction* node);

    private:
      NodeFunctions*	_funcs;
      NodeFunction*	_func;
    };
  }
}

#endif /* !NODEFUNCTIONS_HH_ */
