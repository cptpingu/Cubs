#ifndef NODEDECLARATION_HH_
# define NODEDECLARATION_HH_

# include "Node.hh"
# include "NodeDeclarationBody.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** declaration ::= "var" declaration_body ";"
    **
    */
    class NodeDeclaration : public Node
    {
    public:
      NodeDeclaration();
      virtual ~NodeDeclaration();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeDeclarationBody* getBody() const;
      void setBody(NodeDeclarationBody* node);

    private:
      NodeDeclarationBody*		_body;
    };
  }
}

#endif /* !NODEDECLARATION_HH_ */
