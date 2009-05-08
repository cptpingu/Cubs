#ifndef NODEIDFUNC_HH_
# define NODEIDFUNC_HH_

# include "TypedNode.hh"
# include "Symbol.hh"
# include "NodeFunction.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** idfunc ::= [a-zA-Z]([a-zA-Z0-9_]*[a-zA-Z0-9])?
    */
    class NodeIdFunc : public TypedNode
    {
    public:
      NodeIdFunc();
      virtual ~NodeIdFunc();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      const std::string& getId() const;
      void setId(const std::string& id);
      bool isDeclaration() const;
      void setDeclaration(bool isDecl);
      NodeFunction* getRef() const;
      void setRef(NodeFunction* node);

    private:
      std::string	_id;
      bool		_isDecl;
      NodeFunction*	_ref;
    };
  }
}

#endif /* !NODEIDFUNC_HH_ */
