#ifndef NODEDECLARATIONBODY_HH_
# define NODEDECLARATIONBODY_HH_

# include "Node.hh"
# include "NodeIds.hh"
# include "NodeType.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** declaration_body ::= ids ":" type
    */
    class NodeDeclarationBody : public Node
    {
    public:
      NodeDeclarationBody();
      virtual ~NodeDeclarationBody();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeIds* getIds() const;
      NodeType* getType() const;
      void setIds(NodeIds* node);
      void setType(NodeType* nodeType);

    private:
      NodeIds*		_ids;
      NodeType*		_type;
    };
  }
}

#endif /* !NODEDECLARATIONBODY_HH_ */
