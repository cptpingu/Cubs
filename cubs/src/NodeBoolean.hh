#ifndef NODEBOOLEAN_HH_
# define NODEBOOLEAN_HH_

# include "Node.hh"
# include "TypedNode.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** boolean ::= true | false
    */
    class NodeBoolean : public TypedNode
    {
    public:
      NodeBoolean();
      virtual ~NodeBoolean();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      bool getBool() const;
      void setBool(const bool b);

    private:
      bool	_bool;
    };
  }
}

#endif /* !NODEBOOLEAN_HH_ */
