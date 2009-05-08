#ifndef NODEFUNCTION_HH_
# define NODEFUNCTION_HH_

# include <vector>
# include "TypedNode.hh"
# include "NodeId.hh"
# include "NodeHeaderFunc.hh"
# include "NodeDeclarations.hh"
# include "NodeCompoundInstr.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** func ::= header_func declarations compound_instruction
    */
    class NodeFunction : public TypedNode
    {
    public:
      NodeFunction();
      virtual ~NodeFunction();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeHeaderFunc* getHeaderFunc() const;
      NodeDeclarations*	getDeclarations() const;
      NodeCompoundInstr* getCompoundInstr() const;
      void setHeaderFunc(NodeHeaderFunc* node);
      void setDeclarations(NodeDeclarations* node);
      void setCompoundInstr(NodeCompoundInstr* node);

    public:
      NodeId* getArgument(const unsigned int pos) const;
      unsigned int nbArgument() const;
      void addArgument(NodeId* node);

    private:
      NodeHeaderFunc*		_headerFunc;
      NodeDeclarations*		_declarations;
      NodeCompoundInstr*	_compoundInstr;
      std::vector<NodeId*>	_args;
    };
  }
}

#endif /* !NODEFUNCTION_HH_ */
