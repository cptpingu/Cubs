#ifndef NODEPROGRAM_HH_
# define NODEPROGRAM_HH_

# include "Node.hh"
# include "NodeDeclarations.hh"
# include "NodeFunctions.hh"
# include "NodeCompoundInstr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** program ::= declarations funcs compound_instruction
    **
    */
    class NodeProgram : public Node
    {
    public:
      NodeProgram();
      virtual ~NodeProgram();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeDeclarations*		getDecls() const;
      NodeFunctions*		getFuncs() const;
      NodeCompoundInstr*	getInstrs() const;
      void setDecls(NodeDeclarations* node);
      void setFuncs(NodeFunctions* node);
      void setInstrs(NodeCompoundInstr* node);

    private:
      NodeDeclarations*		_decls;
      NodeFunctions*		_funcs;
      NodeCompoundInstr*	_instrs;
    };
  }
}
#endif /* !NODEPROGRAM_HH_ */
