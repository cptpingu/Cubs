#ifndef NODEREAD_HH_
# define NODEREAD_HH_

# include "Node.hh"
# include "NodeId.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** read ::= "read" "(" id ")" // builtin
    */
    class NodeRead : public Node
    {
    public:
      NodeRead();
      virtual ~NodeRead();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeId* getId() const;
      void setId(NodeId* node);

    private:
      NodeId*		_id;
    };
  }
}

#endif /* !NODEREAD_HH_ */
