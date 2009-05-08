#ifndef PRETTYPRINTERVISITOR_HH_
# define PRETTYPRINTERVISITOR_HH_

# include <iomanip>
# include <sstream>
# include "BaseVisitor.hh"

namespace MiniCompiler
{
  class PrettyPrinterVisitor : public ConstBaseVisitor
  {
    friend std::ostream&
    operator<<(std::ostream& o, const PrettyPrinterVisitor& v);

  public:
    PrettyPrinterVisitor();
    virtual ~PrettyPrinterVisitor();

  public:
    virtual void visit(const AST::NodeIds* node);
    virtual void visit(const AST::NodeProgram* node);
    virtual void visit(const AST::NodeAffect* node);
    virtual void visit(const AST::NodeIf* node);
    virtual void visit(const AST::NodeRead* node);
    virtual void visit(const AST::NodeArgument* node);
    virtual void visit(const AST::NodeArguments* node);
    virtual void visit(const AST::NodeReturn* node);
    virtual void visit(const AST::NodeExit* node);
    virtual void visit(const AST::NodeCallFunc* node);
    virtual void visit(const AST::NodeOperation* node);
    virtual void visit(const AST::NodeExpression* node);
    virtual void visit(const AST::NodeStringExpr* node);
    virtual void visit(const AST::NodeBoolean* node);
    virtual void visit(const AST::NodeExpressions* node);
    virtual void visit(const AST::NodeInstr* node);
    virtual void visit(const AST::NodeCompoundInstr* node);
    virtual void visit(const AST::NodeFactor* node);
    virtual void visit(const AST::NodeInstrs* node);
    virtual void visit(const AST::NodeType* node);
    virtual void visit(const AST::NodeFunction* node);
    virtual void visit(const AST::NodeWhile* node);
    virtual void visit(const AST::NodeDeclarationBody* node);
    virtual void visit(const AST::NodeFunctions* node);
    virtual void visit(const AST::NodeNumber* node);
    virtual void visit(const AST::NodeDeclaration* node);
    virtual void visit(const AST::NodeHeaderFunc* node);
    virtual void visit(const AST::NodeDeclarations* node);
    virtual void visit(const AST::NodeId* node);
    virtual void visit(const AST::NodeIdFunc* node);
    virtual void visit(const AST::NodePrint* node);

  protected:
    void print(std::ostream& o) const;

  protected:
    std::stringstream	_indent;
    unsigned int	_tab;
  };
}

#endif /* !PRETTYPRINTERVISITOR_HH_ */
