#ifndef NODEDECLARATIONS_HH_
# define NODEDECLARATIONS_HH_

# include "Node.hh"
# include "NodeDeclaration.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** declarations := declaration
    **               | declaration declarations
    **
    */
    class NodeDeclarations : public Node
    {
    public:
      NodeDeclarations();
      virtual ~NodeDeclarations();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeDeclaration* getDeclaration() const;
      NodeDeclarations* getDeclarations() const;
      void setDeclaration(NodeDeclaration* node);
      void setDeclarations(NodeDeclarations* node);

    private:
      NodeDeclaration*		_decl;
      NodeDeclarations*		_decls;
    };
  }
}

#endif /* !NODEDECLARATIONS_HH_ */
