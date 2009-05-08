#ifndef NODEARGUMENT_HH_
# define NODEARGUMENT_HH_

# include "Node.hh"
# include "NodeArguments.hh"
# include "NodeDeclarationBody.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** argument ::= declaration_body
    **            | declaration_body "," arguments
    */
    class NodeArgument : public Node
    {
    public:
      NodeArgument();
      virtual ~NodeArgument();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeDeclarationBody* getDeclarationBody() const;
      NodeArguments* getArguments() const;
      void setDeclarationBody(NodeDeclarationBody* node);
      void setArguments(NodeArguments* node);

    private:
      NodeDeclarationBody*	_declarationBody;
      NodeArguments*		_arguments;
    };
  }
}

#endif /* !NODEARGUMENT_HH_ */
