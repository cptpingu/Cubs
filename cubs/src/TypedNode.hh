#ifndef TYPEDNODE_HH_
# define TYPEDNODE_HH_

# include "Utils.hh"
# include "Node.hh"

namespace MiniCompiler
{
  namespace AST
  {
    class TypedNode : public Node
    {
    public:
      TypedNode();
      virtual ~TypedNode();

    public:
      Type::type getComputedType() const;
      void setComputedType(const Type::type type);

    protected:
      Type::type	_computedType;
    };
  }
}

# include "TypedNode.hxx"

#endif /* !TYPEDNODE_HH_ */
