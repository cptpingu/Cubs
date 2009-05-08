#ifndef NODETYPE_HH_
# define NODETYPE_HH_

# include "TypedNode.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** type ::= "integer" | "string" | "boolean"
    */
    class NodeType : public TypedNode
    {
    public:
      NodeType();
      virtual ~NodeType();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      const std::string& getType() const;
      void setType(const std::string& type);

    private:
      std::string	_type;
    };
  }
}

#endif /* !NODETYPE_HH_ */
