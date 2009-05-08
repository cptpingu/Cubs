#ifndef NODENUMBER_HH_
# define NODENUMBER_HH_

# include "Node.hh"
# include "TypedNode.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** number ::= [0-9]+
    */
    class NodeNumber : public TypedNode
    {
    public:
      NodeNumber();
      virtual ~NodeNumber();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      int getNumber() const;
      void setNumber(int nb);

    private:
      int	_number;
    };
  }
}

#endif /* !NODENUMBER_HH_ */
