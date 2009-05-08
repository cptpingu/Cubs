#ifndef NODEID_HH_
# define NODEID_HH_

# include "TypedNode.hh"
# include "Symbol.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** id ::= [a-zA-Z]([a-zA-Z0-9_]*[a-zA-Z0-9])?
    */
    class NodeId : public TypedNode
    {
    public:
      NodeId();
      virtual ~NodeId();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      const std::string& getId() const;
      void setId(const std::string& id);
      bool isDeclaration() const;
      void setDeclaration(bool isDecl);
      NodeId* getRef() const;
      void setRef(NodeId* node);

    private:
      std::string	_id;
      bool		_isDecl;
      NodeId*		_ref;
    };
  }
}

#endif /* !NODEID_HH_ */
