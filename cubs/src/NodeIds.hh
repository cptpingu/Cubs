#ifndef NODEIDS_HH_
# define NODEIDS_HH_

# include "Node.hh"
# include "NodeId.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** ids ::= id
    **       | id "," ids
    */
    class NodeIds : public Node
    {
    public:
      NodeIds();
      virtual ~NodeIds();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeId* getId() const;
      NodeIds* getIds() const;
      void setId(NodeId* id);
      void setIds(NodeIds* node);

    private:
      NodeId*		_id;
      NodeIds*		_ids;
    };
  }
}

#endif /* !NODEIDS_HH_ */
