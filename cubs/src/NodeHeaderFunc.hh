#ifndef NODEHEADERFUNC_HH_
# define NODEHEADERFUNC_HH_

# include "TypedNode.hh"
# include "NodeArguments.hh"
# include "NodeIdFunc.hh"
# include "NodeType.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** header_func ::= "function" id "(" arguments ")" ":" type ";"
    */
    class NodeHeaderFunc : public TypedNode
    {
    public:
      NodeHeaderFunc();
      virtual ~NodeHeaderFunc();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeIdFunc* getId() const;
      NodeType* getType() const;
      NodeArguments* getArguments() const;
      void setId(NodeIdFunc* id);
      void setType(NodeType* type);
      void setArguments(NodeArguments* node);

    private:
      NodeIdFunc*	_id;
      NodeType*		_type;
      NodeArguments*	_arguments;
    };
  }
}

#endif /* !NODEHEADERFUNC_HH_ */
