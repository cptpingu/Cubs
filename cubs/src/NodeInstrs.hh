#ifndef NODEINSTRS_HH_
# define NODEINSTRS_HH_

# include "Node.hh"
# include "NodeInstr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** instructions ::= instruction
    **                | instruction instructions
    **
    */
    class NodeInstrs : public Node
    {
    public:
      NodeInstrs();
      virtual ~NodeInstrs();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeInstrs* getInstrs() const;
      NodeInstr* getInstr() const;
      void setInstrs(NodeInstrs* node);
      void setInstr(NodeInstr* node);

    private:
      NodeInstrs*		_instrs;
      NodeInstr*		_instr;
    };
  }
}
#endif /* !NODEINSTRS_HH_ */
